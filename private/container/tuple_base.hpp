#pragma once
#include <type_traits>
#include <utility>

namespace xme::detail {
template<typename... T>
struct TypeList {};

template<typename... T, typename... U>
constexpr auto operator+(TypeList<T...>, TypeList<U...>) {
    return TypeList<T..., U...>{};
}

template<std::size_t I, typename T>
struct TupleElement {
    constexpr auto operator[](std::integral_constant<std::size_t, I>) & noexcept -> T& {
        return value;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, I>) const& noexcept
        -> const T& {
        return value;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, I>) && noexcept -> T&& {
        return static_cast<TupleElement&&>(*this).value;
    }

    constexpr auto operator<=>(const TupleElement&) const = default;
    
    constexpr bool operator==(const TupleElement&) const = default;

    static constexpr T declval(std::integral_constant<std::size_t, I>) {
        static_assert(false, "This should only be used to get the type of the element");
    }
    
    [[no_unique_address]] T value;
};

template<typename... TupElem>
struct TypeMap : TupElem... {
    using TupElem::operator[]...;
    using TupElem::declval...;
    using base_list = TypeList<TupElem...>;

    constexpr auto operator<=>(const TypeMap&) const = default;
    constexpr bool operator==(const TypeMap&) const = default;
};

template<typename IndexSequence, typename... T>
struct GetTupleBase;

template<std::size_t... I, typename... T>
struct GetTupleBase<std::index_sequence<I...>, T...> {
    using type = TypeMap<TupleElement<I, T>...>;
};

template<typename... T>
using tuple_base = GetTupleBase<std::make_index_sequence<sizeof...(T)>, T...>::type;
} // namespace xme::detail