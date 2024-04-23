#pragma once
#include "xme/ranges/base.hpp"
#include <bits/ranges_base.h>
#include <concepts>
#include <initializer_list>
#include <type_traits>
#include <xme/ranges/traits.hpp>
#include <xme/ranges/access.hpp>

namespace xme::ranges {
namespace detail {
template<typename T>
inline constexpr bool is_initializer_list = false;

template<typename T>
inline constexpr bool is_initializer_list<std::initializer_list<T>> = true;
}  // namespace detail
template<typename R>
concept CRange = requires(R& r) {
    ranges::begin(r);
    ranges::end(r);
};

template<typename R>
concept CBorrowedRange = CRange<R> && detail::basic_borrowed_range<R>;

template<typename R>
concept CSizedRange = CRange<R> && requires(R& r) { ranges::size(r); };

template<typename R>
concept CView = CRange<R> && std::movable<R> || enable_view<R>;

template<typename R>
concept CInputRange = CRange<R> && std::input_iterator<ranges::iterator_t<R>>;

template<typename R, typename T>
concept COutputRange = CRange<R> && std::output_iterator<ranges::iterator_t<R>, T>;

template<typename R>
concept CForwardRange = CInputRange<R> && std::forward_iterator<ranges::iterator_t<R>>;

template<typename R>
concept CBidirectionalRange =
  CForwardRange<R> && std::bidirectional_iterator<ranges::iterator_t<R>>;

template<typename R>
concept CRandomAccessRange =
  CBidirectionalRange<R> && std::random_access_iterator<ranges::iterator_t<R>>;

template<typename R>
concept CContiguousRange =
  CRandomAccessRange<R> && std::contiguous_iterator<ranges::iterator_t<R>> && requires(R& r) {
      { ranges::data(r) } -> std::same_as<std::add_pointer_t<ranges::range_reference_t<R>>>;
  };

template<typename R>
concept CCommonRange = CRange<R> && std::same_as<ranges::iterator_t<R>, ranges::sentinel_t<R>>;

template<typename R>
concept CViewableRange =
  CRange<R>
  && ((CView<std::remove_cvref_t<R>> && std::constructible_from<std::remove_cvref_t<R>, R>)
      || (!CView<std::remove_cvref_t<R>>
          && (std::is_lvalue_reference_v<R>
              || (std::movable<std::remove_reference_t<R>>
                  && detail::is_initializer_list<std::remove_cvref_t<R>>))));

template<typename R>
concept CConstantRange = CInputRange<R> && CConstantIterator<ranges::iterator_t<R>>;
}  // namespace xme::ranges