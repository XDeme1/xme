#pragma once
#include "aligned_data.hpp"
#include "container_policy.hpp"
#include <atomic>
#include <memory>
#include <ranges>
#include <vector>

namespace xme {

template<typename T, std::size_t Size, typename AllocPolicy = DynamicAllocation<std::allocator<T>>>
    requires(is_power_of_2<Size>)
class SPSCQueue;

template<typename T, std::size_t Size>
    requires(is_power_of_2<Size>)
class SPSCQueue<T, Size, StaticAllocation> {
public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::SPSCQueue must have a non-const and non-volatile T");

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    
    constexpr SPSCQueue() = default;

    constexpr ~SPSCQueue()
        requires(std::is_trivially_destructible_v<T>)
    = default;
    
    constexpr 
    constexpr ~SPSCQueue() noexcept { clear(); }

    constexpr auto readAvailable() const noexcept -> std::size_t {
        std::size_t write_index = m_write_index.load(std::memory_order_acquire);
        std::size_t read_index = m_read_index.load(std::memory_order_relaxed);
        if (write_index >= read_index)
            return write_index - read_index;
        return write_index + Size - read_index;
    }

    constexpr void clear() noexcept {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            while (m_read_index != m_write_index) {
                std::ranges::destroy_at(&m_data[m_data]);
                m_read_index = nextIndex(m_read_index);
            }
        }
    }

    template<std::convertible_to<T> U>
    constexpr bool push(U&& value) {
        return emplace(std::forward<U>(value));
    }

    constexpr bool pop(T& out_value) {
        const std::size_t write_index = m_write_index.load(std::memory_order_acquire);
        const std::size_t read_index = m_read_index.load(std::memory_order_relaxed);
        if(isEmpty(write_index, read_index))
            return false;

        out_value = std::move(m_data[read_index]);
        std::ranges::destroy_at(&m_data[read_index]);
        m_read_index.store(nextIndex(read_index), std::memory_order_release);
        return true;
    }

    template<typename... Args>
    constexpr bool emplace(Args&&... args) {
        const std::size_t next = nextIndex(m_write_index.load(std::memory_order_relaxed));
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
        if (isEmpty(write_index, read_index))
            return false;

        fn(std::move(m_data[read_index]));
        std::ranges::destroy_at(&m_data[read_index]);
        m_read_index.store(nextIndex(read_index), std::memory_order_release);
        return true;
    }

private:
    constexpr bool isEmpty(std::size_t write_index, std::size_t read_index) {
        return write_index == read_index;
    }

    constexpr auto nextIndex(std::size_t index) const noexcept -> std::size_t {
        return (index + 1) & mask;
    }

    static constexpr std::size_t mask = Size - 1;

    xme::AlignedData<T, Size> m_data;
    alignas(64) std::atomic<std::size_t> m_write_index = 0;
    alignas(64) std::atomic<std::size_t> m_read_index = 0;
};

template<typename T, std::size_t Size, typename Alloc>
    requires(is_power_of_2<Size>)
class SPSCQueue<T, Size, DynamicAllocation<Alloc>> {


    static constexpr std::size_t mask = Size - 1;

    xme::AlignedData<T, Size> m_data;
    alignas(64) std::atomic<std::size_t> m_write_index = 0;
    alignas(64) std::atomic<std::size_t> m_read_index = 0;
};
} // namespace xme