#pragma once
#include "iterator_traits.hpp"
#include <xme/core/concepts/different_from.hpp>

namespace xme {
template<std::input_iterator It>
class ConstIterator {
private:
    using reference = iter_const_reference_t<It>;
    using traits    = std::iterator_traits<It>;

    static constexpr auto get_iterator_concept() noexcept {
        if constexpr(std::contiguous_iterator<It>)
            return std::contiguous_iterator_tag{};
        else if constexpr(std::random_access_iterator<It>)
            return std::random_access_iterator_tag{};
        else if constexpr(std::bidirectional_iterator<It>)
            return std::bidirectional_iterator_tag{};
        else if constexpr(std::forward_iterator<It>)
            return std::forward_iterator_tag{};
        else
            return std::input_iterator_tag{};
    }

public:
    using difference_type = std::iter_difference_t<It>;
    using value_type      = std::iter_value_t<It>;
    using iterator_category =
      std::conditional_t<std::forward_iterator<It>, typename traits::iterator_category, void>;
    using iterator_concept = decltype(get_iterator_concept());

    constexpr ConstIterator() noexcept = default;

    constexpr ConstIterator(It it) noexcept : m_current(it) {}

    template<std::convertible_to<It> U>
    constexpr ConstIterator(ConstIterator<U> other) noexcept : m_current{other} {}

    template<CDifferentFrom<ConstIterator> T>
        requires std::convertible_to<T, It>
    constexpr ConstIterator(T&& it) noexcept : m_current(std::forward<T>(it)) {}

    constexpr auto operator->() const noexcept -> const auto* {
        if constexpr(std::contiguous_iterator<It>)
            return std::to_address(m_current);
        else
            return std::addressof(*m_current);
    }

    constexpr auto operator*() const noexcept -> reference { return *m_current; }

    constexpr auto operator++() noexcept -> ConstIterator& {
        ++m_current;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> ConstIterator
        requires std::forward_iterator<It>
    {
        ConstIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    constexpr auto operator--() noexcept -> ConstIterator&
        requires std::bidirectional_iterator<It>
    {
        --m_current;
        return *this;
    }

    constexpr auto operator--(int) noexcept -> ConstIterator
        requires std::bidirectional_iterator<It>
    {
        ConstIterator tmp(*this);
        --(*this);
        return tmp;
    }

    constexpr auto operator+(difference_type n) const noexcept -> ConstIterator
        requires std::random_access_iterator<It>
    {
        return m_current + n;
    }

    friend constexpr auto operator+(difference_type n,
                                    const ConstIterator& rhs) noexcept -> ConstIterator
        requires std::random_access_iterator<It>
    {
        return n + rhs.m_current;
    }

    constexpr auto operator-(difference_type n) const noexcept -> ConstIterator
        requires std::random_access_iterator<It>
    {
        return m_current - n;
    }

    template<std::sized_sentinel_for<It> Sent>
    constexpr auto operator-(const Sent& sent) const noexcept -> difference_type {
        return m_current - sent;
    }

    template<CDifferentFrom<ConstIterator> Sent>
        requires std::sized_sentinel_for<Sent, It>
    friend constexpr auto operator-(const Sent& sent,
                                    const ConstIterator& it) noexcept -> difference_type {
        return sent - it.m_current;
    }

    constexpr auto operator+=(difference_type n) noexcept -> ConstIterator&
        requires std::random_access_iterator<It>
    {
        m_current += n;
        return *this;
    }

    constexpr auto operator-=(difference_type n) noexcept -> ConstIterator&
        requires std::random_access_iterator<It>
    {
        m_current -= n;
        return *this;
    }

    constexpr auto operator[](difference_type n) const noexcept -> reference {
        return m_current[n];
    }

    template<std::sentinel_for<It> Sent>
    constexpr bool operator==(const Sent& sent) const noexcept {
        return m_current == sent;
    }

    constexpr bool operator<(const ConstIterator& it) const noexcept
        requires std::random_access_iterator<It>
    {
        return m_current < it.m_current;
    }

    constexpr bool operator>(const ConstIterator& it) const noexcept
        requires std::random_access_iterator<It>
    {
        return m_current > it.m_current;
    }

    constexpr bool operator<=(const ConstIterator& it) const noexcept
        requires std::random_access_iterator<It>
    {
        return m_current <= it.m_current;
    }

    constexpr bool operator>=(const ConstIterator& it) const noexcept
        requires std::random_access_iterator<It>
    {
        return m_current >= it.m_current;
    }

    constexpr auto operator<=>(const ConstIterator& it) const noexcept
        requires std::random_access_iterator<It> && std::three_way_comparable<It>
    {
        return m_current <=> it.m_current;
    }

    template<CDifferentFrom<ConstIterator> OtherIt>
        requires std::random_access_iterator<It> && std::totally_ordered_with<It, OtherIt>
    constexpr auto operator<(const OtherIt& it) const noexcept {
        return m_current < it;
    }

    template<CDifferentFrom<ConstIterator> OtherIt>
        requires std::random_access_iterator<It> && std::totally_ordered_with<It, OtherIt>
    constexpr auto operator>(const OtherIt& it) const noexcept {
        return m_current > it;
    }

    template<CDifferentFrom<ConstIterator> OtherIt>
        requires std::random_access_iterator<It> && std::totally_ordered_with<It, OtherIt>
    constexpr auto operator<=(const OtherIt& it) const noexcept {
        return m_current <= it;
    }

    template<CDifferentFrom<ConstIterator> OtherIt>
        requires std::random_access_iterator<It> && std::totally_ordered_with<It, OtherIt>
    constexpr auto operator>=(const OtherIt& it) const noexcept {
        return m_current >= it;
    }

    template<CDifferentFrom<ConstIterator> OtherIt>
        requires std::random_access_iterator<It> && std::totally_ordered_with<It, OtherIt>
                 && std::three_way_comparable_with<It, OtherIt>
    constexpr auto operator<=>(const OtherIt& it) const noexcept {
        return m_current <=> it;
    }

private:
    It m_current{};
};
}  // namespace xme