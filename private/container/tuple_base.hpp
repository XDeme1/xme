#pragma once
#include <type_traits>
#include <utility>

namespace xme {
template<typename...T>
struct Tuple;
}

namespace xme::detail {
template<typename... T>
struct TypeList {};

template<typename... T, typename... U>
constexpr auto operator+(TypeList<T...>, TypeList<U...>) {
    return TypeList<T..., U...>{};
}

template<std::size_t I, typename T>
struct TupleElement {
    static constexpr T declval(std::integral_constant<std::size_t, I>) {
        static_assert(false, "This should only be used to get the type of the element");
    }

    [[no_unique_address]] T value;

    constexpr auto operator[](std::integral_constant<std::size_t, I>) & -> T& {
        return value;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, I>) const& -> const T& {
        return value;
    }

    constexpr auto operator[](std::integral_constant<std::size_t, I>) && -> T&& {
        return static_cast<TupleElement&&>(*this).value;
    }

    constexpr auto operator<=>(const TupleElement&) const = default;
    constexpr bool operator==(const TupleElement&) const = default;
};

template<typename... TupElem>
struct TypeMap : TupElem... {
    using TupElem::operator[]...;
    using TupElem::declval...;
    using type_list = TypeList<TupElem...>;

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

template<typename T>
struct IsTupleHelper {
    static constexpr bool value = false;
};

template<typename...T>
struct IsTupleHelper<xme::Tuple<T...>> {
    static constexpr bool value = true;
};

template<typename T>
struct IsTuple {
    static constexpr bool value = IsTupleHelper<std::remove_cv_t<T>>::value;
};

template<typename T>
constexpr bool is_tuple_v = IsTuple<T>::value;
} // namespace xme::detail