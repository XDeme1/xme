// IWYU pragma: private, include <xme/ranges/access.hpp>
#pragma once
#include "begin.hpp"
#include "xme/ranges/base.hpp"
#include <iterator>
#include <memory>
#include <type_traits>

namespace xme::ranges {
namespace detail {
template<typename T>
concept pointer_to_object = std::is_pointer_v<T> && std::is_object_v<std::remove_pointer_t<T>>;

template<typename T>
concept member_data = requires(T& t) {
    { decay_copy(t.data()) } -> pointer_to_object;
};

template<typename T>
concept contiguous_begin = requires(T& t) {
    { ranges::begin(t) } -> std::contiguous_iterator;
};
}  // namespace detail

struct {
    template<detail::basic_borrowed_range T>
        requires detail::member_data<T> || detail::contiguous_begin<T>
    constexpr auto operator()(T&& t) const noexcept {
        if constexpr(detail::member_data<T>)
            return t.data();
        else
            return std::to_address(ranges::begin(t));
    }
} inline constexpr data;
}  // namespace xme::ranges