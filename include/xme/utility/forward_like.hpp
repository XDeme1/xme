#pragma once
#include <type_traits>
#include <utility>

namespace xme {
template<typename Like, typename T>
constexpr auto forward_like(T&& value) noexcept -> decltype(auto) {
    constexpr bool is_adding_const = std::is_const_v<std::remove_reference_t<Like>>;
    if constexpr(std::is_lvalue_reference_v<Like&&>) {
        if constexpr(is_adding_const)
            return std::as_const(value);
        else
            return static_cast<T&>(value);
    }
    else {
        if constexpr(is_adding_const)
            return std::move(std::as_const(value));
        else
            return std::move(value);
    }
}
}