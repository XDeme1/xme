#pragma once
#include <atomic>

namespace xme::detail {
template<typename T, std::size_t Size>
class SPSCQueueBase {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    
    constexpr auto readAvailable() const noexcept -> std::size_t {
        std::size_t write_index = m_write_index.load(std::memory_order_acquire);
        std::size_t read_index = m_read_index.load(std::memory_order_relaxed);
        if (write_index >= read_index)
            return write_index - read_index;
        return write_index + Size - read_index;
    }

    constexpr auto writeAvailable() const noexcept -> std::size_t {
        std::size_t write_index = m_write_index.load(std::memory_order_relaxed);
        std::size_t read_index = m_read_index.load(std::memory_order_acquire);
        std::size_t diff = read_index - write_index - 1;
        if(diff >= read_index)
            diff += Size;
        return diff;
    }

protected:
    constexpr bool isEmpty(std::size_t write_index, std::size_t read_index) {
        return write_index == read_index;
    }

    constexpr auto nextIndex(std::size_t index) const noexcept -> std::size_t {
        return (index + 1) & mask;
    }

    static constexpr std::size_t mask = Size - 1;

    std::atomic<std::size_t> m_write_index = 0;
    char padding[64 - sizeof(std::size_t)]; // force write and read index to be on different cache lines
    std::atomic<std::size_t> m_read_index = 0;
};
}