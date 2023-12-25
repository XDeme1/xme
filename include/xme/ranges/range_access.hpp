#pragma once
#include <iterator>
#include <xme/core/concepts/convertible.hpp>
#include "../../../private/ranges/class_or_enum.hpp"

namespace xme::ranges {
template<typename>
inline constexpr bool enable_borrowed_range = false;

namespace detail::_access {
template<typename T>
    requires xme::convertible_to_c<T, std::decay_t<T>>
constexpr auto decay_copy(T&& t)
  noexcept(std::is_nothrow_convertible_v<T, std::decay_t<T>>) -> std::decay_t<T> {
    return static_cast<std::decay_t<T>>(static_cast<T&&>(t));
}

template<typename T>
concept simple_borrowed_range_c =
  std::is_lvalue_reference_v<T> || enable_borrowed_range<std::remove_cvref_t<T>>;

template<typename T>
concept member_begin_c = requires(T& t) {
    { decay_copy(t.begin()) } -> std::input_or_output_iterator;
};

template<typename T>
concept adl_begin_c = class_or_enum_c<std::remove_reference_t<T>> && requires(T& t) {
    { decay_copy(begin(t)) } -> std::input_or_output_iterator;
};

struct Begin {
private:
    template<typename T>
    [[nodiscard]]
    constexpr bool is_noexcept() const noexcept {
        if constexpr(std::is_array_v<std::remove_reference_t<T>>)
            return true;
        else if(member_begin_c<T>)
            return noexcept(decay_copy(std::declval<T&>().begin()));
        else {
            return noexcept(decay_copy(begin(std::declval<T&>())));
        }
    }

public:
    template<simple_borrowed_range_c T>
        requires std::is_array_v<std::remove_reference_t<T>> || member_begin_c<T> || adl_begin_c<T>
    constexpr auto operator()(T&& t) const noexcept(is_noexcept<T>()) {
        if constexpr(std::is_array_v<std::remove_reference_t<T>>)
            return t + 0;
        else if constexpr(member_begin_c<T>)
            return t.begin();
        else
            return begin(t);
    }
};

template<typename T>
using iterator_t = decltype(std::declval<Begin&>()(std::declval<T&>()));

template<typename T>
concept member_end_c = requires(T& t) {
    { decay_copy(t.end()) } -> std::sentinel_for<iterator_t<T>>;
};

template<typename T>
concept adl_end_c = class_or_enum_c<std::remove_reference_t<T>> && requires(T& t) {
    { decay_copy(end(t)) } -> std::sentinel_for<iterator_t<T>>;
};

struct End {
private:
    template<typename T>
    [[nodiscard]]
    constexpr bool is_noexcept() const noexcept {
        if constexpr(std::is_bounded_array_v<std::remove_reference_t<T>>)
            return true;
        else if constexpr(member_end_c<T>)
            return noexcept(decay_copy(std::declval<T&>.end()));
        else
            return noexcept(decay_copy(end(std::declval<T&>())));
    }

public:
    template<simple_borrowed_range_c T>
        requires std::is_bounded_array_v<std::remove_reference_t<T>> || member_end_c<T>
                   || adl_end_c<T>
    constexpr auto operator()(T&& t) const
      noexcept(is_noexcept<T>()) -> std::sentinel_for<iterator_t<T>> auto {
        if constexpr(std::is_bounded_array_v<std::remove_reference_t<T>>)
            return t + std::extent_v<std::remove_reference_t<T>>;
        else if constexpr(member_end_c<T>)
            return t.end();
        else
            return end(t);
    }
};

}  // namespace detail::_access

inline constexpr detail::_access::Begin begin;
inline constexpr detail::_access::End end;
}  // namespace xme::ranges
