#pragma once
#include <type_traits>
#include <utility>

#include <xme/setup.hpp>
#include <xme/core/utility/forward_like.hpp>

namespace xme::detail {
template<typename... T>
struct TypeList {};

template<typename... T, typename... U>
constexpr auto operator+(TypeList<T...>, TypeList<U...>) {
    return TypeList<T..., U...>{};
}

template<std::size_t I, typename T>
struct TupleElement {
#if defined(__cpp_explicit_this_parameter)
    template<typename Self>
    [[nodiscard]]
    constexpr auto operator[](this Self&& self,
                              std::integral_constant<std::size_t, I>) noexcept -> auto&& {
        return xme::forward_like<Self>(self).value;
    }
#else
    [[nodiscard]]
    constexpr auto operator[](std::integral_constant<std::size_t, I>) & noexcept -> T& {
        return value;
    }

    [[nodiscard]]
    constexpr auto operator[](std::integral_constant<std::size_t, I>) const& noexcept -> const T& {
        return value;
    }

    [[nodiscard]]
    constexpr auto operator[](std::integral_constant<std::size_t, I>) && noexcept -> T&& {
        return static_cast<TupleElement&&>(*this).value;
    }
#endif

    XME_CONSTEXPR20 auto operator<=>(const TupleElement&) const = default;

    XME_CONSTEXPR20 bool operator==(const TupleElement&) const = default;

    static constexpr T declval(std::integral_constant<std::size_t, I>);

    [[no_unique_address]]
    T value;
};

template<typename... TupElem>
struct TypeMap : TupElem... {
    using TupElem::operator[]...;
    using TupElem::declval...;
    using base_list = TypeList<TupElem...>;

    XME_CONSTEXPR20 auto operator<=>(const TypeMap&) const = default;
    XME_CONSTEXPR20 bool operator==(const TypeMap&) const  = default;
};

template<typename IndexSequence, typename... T>
struct GetTupleBase;

template<std::size_t... I, typename... T>
struct GetTupleBase<std::index_sequence<I...>, T...> {
    using type = TypeMap<TupleElement<I, T>...>;
};

template<typename... T>
using tuple_base = typename GetTupleBase<std::make_index_sequence<sizeof...(T)>, T...>::type;
}  // namespace xme::detail
