#pragma once
#include <xme/core/concepts/same_as.hpp>
#include <xme/core/concepts/assignable.hpp>
#include <xme/core/concepts/constructible.hpp>
#include "../../../private/ranges/class_or_enum.hpp"

namespace xme::ranges {
namespace detail::_swap {
template<typename T>
constexpr void swap(T&, T&) = delete;

template<typename T, typename U>
concept adl_swap = (detail::class_or_enum_c<std::remove_reference_t<T>>
                    || detail::class_or_enum_c<std::remove_reference_t<U>>)&&requires(T& t, U& u) {
    swap(static_cast<T&&>(t), static_cast<U&&>(u));
};

struct Swap {
private:
    template<typename T, typename U>
    static constexpr bool is_noexcept() noexcept {
        if constexpr(adl_swap<T, U>) {
            return noexcept(swap(std::declval<T>(), std::declval<U>()));
        }
        return std::is_nothrow_move_constructible_v<std::remove_reference_t<T>>
               && std::is_nothrow_move_assignable_v<std::remove_reference_t<T>>;
    }

public:
    template<typename T, typename U>
        requires adl_swap<T, U>
                 || (same_as_c<T, U> && std::is_lvalue_reference_v<T>
                     && move_constructible_c<std::remove_reference_t<T>>
                     && assignable_from_c<T, std::remove_reference_t<T>>)
    constexpr void operator()(T&& t, U&& u) const noexcept(is_noexcept<T, U>()) {
        if constexpr(adl_swap<T, U>) {
            swap(static_cast<T&&>(t), static_cast<U&&>(u));
        }
        else {
            auto tmp{static_cast<std::remove_reference_t<T>&&>(t)};
            t = static_cast<std::remove_reference_t<T>&&>(u);
            u = static_cast<std::remove_reference_t<T>&&>(tmp);
        }
    }

    template<typename T, typename U, std::size_t N>
        requires requires(const Swap& s, T& t, U& u) { s(t, u); }
    constexpr void operator()(T (&t)[N], U (&u)[N]) const
      noexcept(noexcept(std::declval<const Swap&>()(*t, *u))) {
        for(std::size_t i = 0; i < N; ++i) {
            (*this)(t[i], u[i]);
        }
    }
};
};  // namespace detail::_swap

inline constexpr detail::_swap::Swap swap;
}  // namespace xme::ranges
