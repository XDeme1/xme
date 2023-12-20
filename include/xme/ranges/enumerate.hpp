#pragma once
#include <iterator>
#include <ranges>
#include <xme/container/tuple.hpp>
#include "../../../private/ranges/setup.hpp"
#include "all.hpp"

namespace xme::ranges {
namespace detail {
template<typename R>
concept CRangeMovableReference =
  std::ranges::range<R> && std::move_constructible<std::ranges::range_reference_t<R>>
  && std::move_constructible<std::ranges::range_rvalue_reference_t<R>>;
}
template<std::ranges::view V>
    requires(detail::CRangeMovableReference<V>)
struct EnumerateView : public ViewInterface<EnumerateView<V>> {
private:
    template<bool Const>
    struct Iterator;

    template<bool Const>
    struct Sentinel;

public:
    constexpr EnumerateView()
        requires std::default_initializable<V>
    = default;

    constexpr EnumerateView(V v) : view(std::move(v)) {}

    [[nodiscard]]
    constexpr auto begin() {
        return Iterator<false>(std::ranges::begin(view), 0);
    }

    [[nodiscard]]
    constexpr auto begin() const {
        return Iterator<true>(std::ranges::begin(view), 0);
    }

    [[nodiscard]]
    constexpr auto end() {
        if constexpr(std::ranges::common_range<V> && std::ranges::sized_range<V>)
            return Iterator<false>(std::ranges::end(view), std::ranges::distance(view));
        else
            return Sentinel<false>(std::ranges::end(view));
    }

    [[nodiscard]]
    constexpr auto end() const {
        if constexpr(std::ranges::common_range<const V> && std::ranges::sized_range<const V>)
            return Iterator<true>(std::ranges::end(view), std::ranges::distance(view));
        else
            return Sentinel<true>(std::ranges::end(view));
    }

    [[nodiscard]]
    constexpr auto size() const
        requires(std::ranges::sized_range<V>)
    {
        return std::ranges::size(view);
    }

    V view = V();
};

template<typename V>
EnumerateView(V) -> EnumerateView<xme::views::all_t<V>>;

template<std::ranges::view V>
    requires(detail::CRangeMovableReference<V>)
template<bool Const>
struct EnumerateView<V>::Iterator {
private:
    using base_type = std::conditional_t<Const, const V, V>;
    using iterator  = std::ranges::iterator_t<base_type>;

    static auto consteval get_iterator_concept() {
        if constexpr(std::ranges::random_access_range<base_type>)
            return std::random_access_iterator_tag{};
        else if constexpr(std::ranges::bidirectional_range<base_type>)
            return std::bidirectional_iterator_tag{};
        else if constexpr(std::ranges::forward_range<base_type>)
            return std::forward_iterator_tag{};
        else
            return std::input_iterator_tag{};
    }

    friend EnumerateView;

public:
    using iterator_tag     = std::input_iterator_tag;
    using iterator_concept = decltype(get_iterator_concept());
    using difference_type  = std::ranges::range_difference_t<base_type>;
    using value_type       = xme::Tuple<difference_type, std::ranges::range_value_t<base_type>>;

private:
    using reference_type = xme::Tuple<difference_type, std::ranges::range_reference_t<base_type>>;

    constexpr Iterator(iterator it, difference_type i) : current(std::move(it)), idx(i) {}

public:
    constexpr Iterator()
        requires std::default_initializable<iterator>
    = default;

    constexpr Iterator(Iterator<!Const> other)
        requires(Const) && std::convertible_to<std::ranges::iterator_t<V>, iterator>
      : current(std::move(other.current)), idx(other.idx) {}

    constexpr auto operator*() const -> reference_type { return {idx, *current}; }

    constexpr auto operator++() -> Iterator& {
        ++idx;
        ++current;
        return *this;
    }

    constexpr void operator++(int) { ++(*this); }

    constexpr auto operator++(int) -> Iterator
        requires(std::ranges::forward_range<base_type>)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    constexpr auto operator--() -> Iterator&
        requires(std::ranges::bidirectional_range<base_type>)
    {
        --idx;
        --current;
        return *this;
    }

    constexpr auto operator--(int) -> Iterator
        requires(std::ranges::bidirectional_range<base_type>)
    {
        auto tmp(*this);
        --(*this);
        return tmp;
    }

    constexpr auto operator+(difference_type n) const -> Iterator
        requires(std::ranges::random_access_range<base_type>)
    {
        auto tmp(*this);
        return tmp += n;
    }

    friend constexpr auto operator+(difference_type n, const Iterator& lhs) -> Iterator
        requires(std::ranges::random_access_range<base_type>)
    {
        return lhs + n;
    }

    constexpr auto operator-(difference_type n) const -> Iterator
        requires(std::ranges::random_access_range<base_type>)
    {
        auto tmp(*this);
        return tmp -= n;
    }

    constexpr auto operator-(const Iterator& rhs) const -> difference_type
        requires(std::ranges::random_access_range<base_type>)
    {
        return idx - rhs.idx;
    }

    constexpr auto operator+=(difference_type n) -> Iterator&
        requires(std::ranges::random_access_range<base_type>)
    {
        current += n;
        idx += n;
        return *this;
    }

    constexpr auto operator-=(difference_type n) -> Iterator&
        requires(std::ranges::random_access_range<base_type>)
    {
        current -= n;
        idx -= n;
        return *this;
    }

    constexpr auto operator[](difference_type n) const -> reference_type
        requires(std::ranges::random_access_range<base_type>)
    {
        return {idx + n, current[n]};
    }

    constexpr bool operator==(const Iterator& rhs) const noexcept { return idx == rhs.idx; }

    constexpr auto operator<=>(const Iterator& rhs) const noexcept { return idx <=> rhs.idx; }

    iterator current    = iterator();
    difference_type idx = 0;
};

template<std::ranges::view V>
    requires(detail::CRangeMovableReference<V>)
template<bool Const>
struct EnumerateView<V>::Sentinel {
private:
    using base_type       = std::conditional_t<Const, const V, V>;
    using sentinel        = std::ranges::sentinel_t<base_type>;
    using difference_type = std::ranges::range_difference_t<V>;

    friend EnumerateView;

    constexpr explicit Sentinel(sentinel s) : sent(std::move(s)) {}

public:
    constexpr Sentinel() = default;

    constexpr Sentinel(Sentinel<!Const> other)
        requires(Const) && (std::convertible_to<std::ranges::sentinel_t<V>, sentinel>)
      : sent(std::move(other.sent)) {}

    template<bool OtherConst>
    friend constexpr bool operator==(const Iterator<OtherConst>& lhs,
                                     const Sentinel& rhs) noexcept {
        return lhs.current == rhs.sent;
    }

    template<bool OtherConst>
        requires(std::sized_sentinel_for<
                  sentinel, std::ranges::iterator_t<std::conditional_t<OtherConst, const V, V>>>)
    constexpr auto operator-(const Iterator<OtherConst>& rhs) const -> difference_type {
        return sent - rhs.current;
    }

    template<bool OtherConst>
        requires(std::sized_sentinel_for<
                  sentinel, std::ranges::iterator_t<std::conditional_t<OtherConst, const V, V>>>)
    friend constexpr auto operator-(const Iterator<OtherConst>& lhs,
                                    const Sentinel& rhs) -> difference_type {
        return lhs.current - rhs.sent;
    }

    sentinel sent = sentinel{};
};
}  // namespace xme::ranges

namespace xme::ranges::views {
namespace detail {
struct Enumerate : XME_RANGE_ADAPTOR_CLOSURE(Enumerate) {
    constexpr Enumerate() = default;

    template<std::ranges::viewable_range R>
    constexpr auto operator()(R&& r) const {
        return EnumerateView<xme::views::all_t<R>>(std::forward<R>(r));
    }
};
}  // namespace detail

inline constexpr detail::Enumerate enumerate;
}  // namespace xme::ranges::views

namespace xme {
namespace views = xme::ranges::views;
}

template<typename T>
inline constexpr bool std::ranges::enable_view<xme::ranges::EnumerateView<T>> = true;

template<typename T>
inline constexpr bool std::ranges::enable_borrowed_range<xme::ranges::EnumerateView<T>> =
  std::ranges::enable_borrowed_range<T>;
