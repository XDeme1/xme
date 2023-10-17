#pragma once
#include <atomic>
#include <cassert>
#include <memory>
#include <xme/container/aligned_data.hpp>

namespace xme::detail {
template<typename T>
class SPSCQueueBase {
public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::SPSCQueue must have a non-const and non-volatile T");

    using size_type = std::size_t;

protected:
    constexpr void clear(T* buffer, size_type max_size) noexcept {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            while (m_read_index != m_write_index) {
                std::ranges::destroy_at(buffer + m_read_index);
                m_read_index = this->next_index(m_read_index, max_size);
            }
        } else {
            m_write_index.store(0, std::memory_order_relaxed);
            m_read_index.store(0, std::memory_order_release);
        }
    }


    constexpr auto read_available(size_type max_size) const noexcept -> size_type {
        size_type write_index = m_write_index.load(std::memory_order_acquire);
        size_type read_index = m_read_index.load(std::memory_order_relaxed);
        if (write_index >= read_index)
            return write_index - read_index;
        return write_index + max_size - read_index;
    }

    constexpr auto write_available(size_type max_size) const noexcept -> size_type {
        size_type write_index = m_write_index.load(std::memory_order_relaxed);
        size_type read_index = m_read_index.load(std::memory_order_acquire);
        size_type diff = read_index - write_index - 1;
        if (diff >= read_index)
            diff += max_size;
        return diff;
    }

    constexpr bool is_empty(size_type write_index, size_type read_index) const noexcept {
        return write_index == read_index;
    }

    constexpr auto next_index(size_type index, size_type max_size) const noexcept
        -> size_type {
        return (index + 1) & (max_size - 1);
    }

    template<typename... Args>
    constexpr bool emplace(T* buffer, size_type max_size, Args&&... args) {
        const std::size_t write_index = m_write_index.load(std::memory_order_relaxed);
        const std::size_t next = next_index(write_index, max_size);
        if (next == m_read_index.load(std::memory_order_acquire))
            return false; // SPSCQueue is full
        std::ranges::construct_at(buffer + write_index,
                                  std::forward<Args>(args)...);
        m_write_index.store(next, std::memory_order_release);
        return true;
    }

    constexpr void pop(T* buffer, size_type max_size) {
        const std::size_t read_index = m_read_index.load(std::memory_order_relaxed);
        assert(
            !this->is_empty(m_write_index.load(std::memory_order_acquire), read_index));

        std::ranges::destroy_at(buffer + read_index);
        m_read_index.store(next_index(read_index, max_size), std::memory_order_release);
    }

    template<typename Fun>
    constexpr void consume(T* buffer, size_type max_size, Fun&& fn) {
        const std::size_t read_index = m_read_index.load(std::memory_order_relaxed);
        assert(!this->is_empty(m_write_index.load(std::memory_order_acquire), read_index));

        fn(std::move(buffer[read_index]));
        std::ranges::destroy_at(buffer + read_index);
        m_read_index.store(next_index(read_index, max_size), std::memory_order_release);
    }

    std::atomic<size_type> m_write_index = 0;
    char padding[64 - sizeof(size_type)]; // force write and read index to be on different
                                          // cache lines
    std::atomic<size_type> m_read_index = 0;
};

template<typename T, typename Size>
class StaticSPSCQueue : public SPSCQueueBase<T> {
    using super = SPSCQueueBase<T>;
    using SPSCQueueBase<T>::m_write_index;
    using SPSCQueueBase<T>::m_read_index;

    static constexpr std::size_t capacity = Size::capacity; 
public:
    static_assert(xme::has_single_bit(capacity), "The capacity must be a power of 2");

    constexpr ~StaticSPSCQueue()
        requires(std::is_trivially_destructible_v<T>)
    = default;

    constexpr ~StaticSPSCQueue() noexcept {
        while (m_read_index != m_write_index) {
            std::ranges::destroy_at(data()+m_read_index);
            m_read_index = this->next_index(m_read_index, capacity);
        }
    }

    constexpr auto read_available() const noexcept -> std::size_t {
        return super::read_available(capacity);
    }

    constexpr auto write_available() const noexcept -> std::size_t {
        return super::write_available(capacity);
    }

    constexpr void clear() noexcept {
        super::clear(data(), capacity);
    }

    template<std::convertible_to<T> U>
    constexpr bool push(U&& value) {
        return emplace(std::forward<U>(value));
    }

    template<typename... Args>
    constexpr bool emplace(Args&&... args) {
        return super::emplace(data(), capacity, std::forward<Args>(args)...);
    }

    constexpr void pop() {
        super::pop(data(), capacity);
    }

    template<typename Fun>
    constexpr void consume(Fun&& fn) {
        super::consume(data(), capacity, std::forward<Fun>(fn));
    }

private:
    constexpr auto data() -> T* {
        return m_data.data()->data();
    }
private:
    std::array<xme::AlignedData<T>, capacity> m_data;
};

template<typename T, typename Alloc>
class DynamicSPSCQueue : public SPSCQueueBase<T> {
private:
    using super = SPSCQueueBase<T>;
    using super::m_read_index;
    using super::m_write_index;

public:
    using allocator_type = Alloc;

    constexpr DynamicSPSCQueue(std::size_t capacity) : m_capacity(capacity) {
        m_data = m_allocator.allocate(capacity);
    }

    constexpr ~DynamicSPSCQueue() noexcept {
        while (m_read_index != m_write_index) {
            std::ranges::destroy_at(&m_data[m_read_index]);
            m_read_index = this->next_index(m_read_index, m_capacity);
        }
        m_allocator.deallocate(m_data, m_capacity);
    }

    constexpr auto read_available() const noexcept -> std::size_t {
        return super::read_available(m_capacity);
    }

    constexpr auto write_available() const noexcept -> std::size_t {
        return super::write_available(m_capacity);
    }

    constexpr void clear() noexcept {
        super::clear(m_data, m_capacity);
    }

    template<std::convertible_to<T> U>
    constexpr bool push(U&& value) {
        return emplace(std::forward<U>(value));
    }

    template<typename... Args>
    constexpr bool emplace(Args&&... args) {
        return super::emplace(m_data, m_capacity, std::forward<Args>(args)...);
    }

    constexpr void pop() {
        super::pop(m_data, m_capacity);
    }

    template<typename Fun>
    constexpr void consume(Fun&& fn) {
        super::consume(m_data, m_capacity, std::forward<Fun>(fn));
    }

private:
    T* m_data = nullptr;
    std::size_t m_capacity = 0;
    [[no_unique_address]] Alloc m_allocator;
};
} // namespace xme::detail