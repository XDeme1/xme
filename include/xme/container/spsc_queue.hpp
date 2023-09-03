#pragma once
#include "../../../private/container/spsc_queue_base.hpp"
#include "aligned_data.hpp"
#include "container_policy.hpp"
#include <memory>

namespace xme {

template<typename T, std::size_t Size,
         typename AllocPolicy = DynamicAllocation<std::allocator<T>>>
    requires(is_power_of_2<Size>)
class SPSCQueue {
public:
    static_assert(
        false, "Please Use either DynamicAllocation<Allocator> or StaticAllocation for "
               "the third template argument");
};

template<typename T, std::size_t Size>
    requires(is_power_of_2<Size>)
class SPSCQueue<T, Size, StaticAllocation> : public detail::SPSCQueueBase<T, Size> {
private:
    using super = detail::SPSCQueueBase<T, Size>;
    using super::m_read_index;
    using super::m_write_index;
    using super::mask;

public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::SPSCQueue must have a non-const and non-volatile T");

    constexpr SPSCQueue() = default;

    constexpr ~SPSCQueue()
        requires(std::is_trivially_destructible_v<T>)
    = default;

    constexpr ~SPSCQueue() noexcept { clear(); }

    constexpr void clear() noexcept {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            while (m_read_index != m_write_index) {
                std::ranges::destroy_at(&m_data[m_data]);
                m_read_index = nextIndex(m_read_index);
            }
        } else {
            m_write_index.store(0, std::memory_order_relaxed);
            m_read_index.store(0, std::memory_order_release);
        }
    }

    template<std::convertible_to<T> U>
    constexpr bool push(U&& value) {
        return emplace(std::forward<U>(value));
    }

    constexpr bool pop(T& out_value) {
        const std::size_t write_index = m_write_index.load(std::memory_order_acquire);
        const std::size_t read_index = m_read_index.load(std::memory_order_relaxed);
        if (this->isEmpty(write_index, read_index))
            return false;

        out_value = std::move(m_data[read_index]);
        std::ranges::destroy_at(&m_data[read_index]);
        m_read_index.store(this->nextIndex(read_index), std::memory_order_release);
        return true;
    }

    template<typename... Args>
    constexpr bool emplace(Args&&... args) {
        const std::size_t next =
            this->nextIndex(m_write_index.load(std::memory_order_relaxed));
        if (next == m_read_index.load(std::memory_order_acquire))
            return false; // SPSCQueue is full

        std::ranges::construct_at(&m_data[m_write_index], std::forward<Args>(args)...);
        m_write_index.store(next, std::memory_order_release);
        return true;
    }

    template<typename Fun>
    constexpr bool consume(Fun&& fn) {
        const std::size_t write_index = m_write_index.load(std::memory_order_acquire);
        const std::size_t read_index = m_read_index.load(std::memory_order_relaxed);
        if (this->isEmpty(write_index, read_index))
            return false;

        fn(std::move(m_data[read_index]));
        std::ranges::destroy_at(&m_data[read_index]);
        m_read_index.store(this->nextIndex(read_index), std::memory_order_release);
        return true;
    }

private:
    xme::AlignedData<T, Size> m_data;
};

template<typename T, std::size_t Size, CStatelessAllocator Alloc>
    requires(is_power_of_2<Size>)
class SPSCQueue<T, Size, DynamicAllocation<Alloc>>
    : public detail::SPSCQueueBase<T, Size> {
private:
    using super = detail::SPSCQueueBase<T, Size>;
    using super::m_read_index;
    using super::m_write_index;

public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::SPSCQueue must have a non-const and non-volatile T");
    static_assert(std::is_same_v<T, typename Alloc::value_type>,
                  "xme::SPSCQueue must have the same T as its allocator");

    using allocator_type = Alloc;

    constexpr SPSCQueue() {
        try {
            m_data = m_allocator.allocate(Size);
        } catch (...) {
            m_allocator.deallocate(m_data, Size);
            throw;
        }
    }

    constexpr ~SPSCQueue() noexcept {
        clear();
        m_allocator.deallocate(m_data, Size);
    }

    constexpr void clear() noexcept {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            while (m_read_index != m_write_index) {
                std::ranges::destroy_at(&m_data[m_data]);
                m_read_index = nextIndex(m_read_index);
            }
        } else {
            m_write_index.store(0, std::memory_order_relaxed);
            m_read_index.store(0, std::memory_order_release);
        }
    }

    template<std::convertible_to<T> U>
    constexpr bool push(U&& value) {
        return emplace(std::forward<U>(value));
    }

    constexpr bool pop(T& out_value) {
        const std::size_t write_index = m_write_index.load(std::memory_order_acquire);
        const std::size_t read_index = m_read_index.load(std::memory_order_relaxed);
        if (this->isEmpty(write_index, read_index))
            return false;

        out_value = std::move(m_data[read_index]);
        std::ranges::destroy_at(&m_data[read_index]);
        m_read_index.store(this->nextIndex(read_index), std::memory_order_release);
        return true;
    }

    template<typename... Args>
    constexpr bool emplace(Args&&... args) {
        const std::size_t next =
            this->nextIndex(m_write_index.load(std::memory_order_relaxed));
        if (next == m_read_index.load(std::memory_order_acquire))
            return false; // SPSCQueue is full

        std::ranges::construct_at(&m_data[m_write_index], std::forward<Args>(args)...);
        m_write_index.store(next, std::memory_order_release);
        return true;
    }

    template<typename Fun>
    constexpr bool consume(Fun&& fn) {
        const std::size_t write_index = m_write_index.load(std::memory_order_acquire);
        const std::size_t read_index = m_read_index.load(std::memory_order_relaxed);
        if (this->isEmpty(write_index, read_index))
            return false;

        fn(std::move(m_data[read_index]));
        std::ranges::destroy_at(&m_data[read_index]);
        m_read_index.store(this->nextIndex(read_index), std::memory_order_release);
        return true;
    }

private:
    T* m_data = nullptr;
    [[no_unique_address]] Alloc m_allocator;
};
} // namespace xme