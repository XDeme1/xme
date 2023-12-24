#pragma once
#include <cassert>
#include <memory>
#include "../../../private/container/spsc_queue_base.hpp"
#include "container_policy.hpp"
#include "container.hpp"

namespace xme {
//! SPSCQueue is a single-producer, single-consumer queue.
//! Pushing and poping is wait-free
//! Policy Options:
//!     xme::Capacity<std::size_t>: Creates a compile time sized SPSCQueue.
//!     Allocator: Creates a runtime sized SPSCQueue.
template<typename T, typename Policy = std::allocator<T>>
class SPSCQueue : std::conditional_t<allocator_c<Policy>, detail::DynamicSPSCQueue<T, Policy>,
                                     detail::StaticSPSCQueue<T, Policy>> {
private:
    using super = std::conditional_t<allocator_c<Policy>, detail::DynamicSPSCQueue<T, Policy>,
                                     detail::StaticSPSCQueue<T, Policy>>;

public:
    constexpr SPSCQueue()
        requires(!allocator_c<Policy>)
    = default;

    constexpr SPSCQueue(std::size_t capacity)
        requires(allocator_c<Policy>)
      : super(capacity) {
        assert(std::has_single_bit(capacity) && "capacity must be a power of 2");
    }

    [[nodiscard]]
    constexpr auto read_available() const noexcept -> std::size_t {
        return super::read_available();
    }

    [[nodiscard]]
    constexpr auto write_available() const noexcept -> std::size_t {
        return super::write_available();
    }

    template<std::convertible_to<T> U>
    constexpr bool push(U&& value) {
        return super::push(std::forward<U>(value));
    }

    template<typename... Args>
    constexpr bool emplace(Args&&... args) {
        return super::emplace(std::forward<Args>(args)...);
    }

    constexpr void pop() noexcept { super::pop(); }

    template<typename F>
    constexpr void consume(F&& fn) {
        super::consume(std::forward<F>(fn));
    }

public:
};
}  // namespace xme
