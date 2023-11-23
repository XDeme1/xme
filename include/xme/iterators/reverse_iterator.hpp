#pragma once
#include <iterator>

namespace xme {
template<std::bidirectional_iterator It>
struct ReverseIterator {
private:
    using self            = ReverseIterator<It>;
    using iterator_traits = std::iterator_traits<It>;

public:
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type      = typename iterator_traits::value_type;
    using pointer         = typename iterator_traits::pointer;
    using reference       = typename iterator_traits::reference;

    template<std::bidirectional_iterator>
    friend struct ReverseIterator;

    constexpr ReverseIterator() noexcept = default;

    constexpr ReverseIterator(It it) noexcept : m_current(it) {}

    template<std::convertible_to<It> Iter>
    constexpr ReverseIterator(const ReverseIterator<Iter>& it) noexcept : m_current(it.m_current) {}

    constexpr auto operator->() const noexcept -> pointer {
        if constexpr(std::is_pointer_v<It>)
            return m_current - 1;
        else {
            It tmp{m_current};
            return (--tmp).operator->();
        }
    }
    constexpr auto operator*() const noexcept -> reference {
        if constexpr(std::is_pointer_v<It>)
            return *(m_current - 1);
        else {
            It tmp{m_current};
            return *(--tmp);
        }
    }

    constexpr auto operator++() noexcept -> self& {
        --m_current;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> self {
        self tmp{*this};
        --m_current;
        return tmp;
    }

    constexpr auto operator--() noexcept -> self& {
        ++m_current;
        return *this;
    }

    constexpr auto operator--(int) noexcept -> self {
        self tmp{*this};
        ++m_current;
        return tmp;
    }

    constexpr auto operator+(difference_type n) const noexcept -> self
        requires(std::random_access_iterator<It>)
    {
        return self(m_current - n);
    }

    friend constexpr auto operator+(difference_type n, const self& it) noexcept -> self
        requires(std::random_access_iterator<It>)
    {
        return self(it.m_current - n);
    }

    constexpr auto operator-(difference_type n) const noexcept -> self
        requires(std::random_access_iterator<It>)
    {
        return self(m_current + n);
    }

    friend constexpr auto operator-(difference_type n, const self& it) noexcept -> self
        requires(std::random_access_iterator<It>)
    {
        return self(n + it.m_current);
    }

    friend constexpr auto operator-(const self& lhs, const self& rhs) noexcept -> difference_type
        requires(std::random_access_iterator<It>)
    {
        return rhs.m_current - lhs.m_current;
    }

    constexpr auto operator+=(difference_type n) noexcept -> self&
        requires(std::random_access_iterator<It>)
    {
        m_current -= n;
        return *this;
    }

    constexpr auto operator-=(difference_type n) noexcept -> self&
        requires(std::random_access_iterator<It>)
    {
        m_current += n;
        return *this;
    }

    constexpr auto operator[](difference_type n) const noexcept -> reference
        requires(std::random_access_iterator<It>)
    {
        return *(*this + n);
    }

    constexpr bool operator==(const self& rhs) const noexcept = default;

    constexpr auto operator<=>(const self& rhs) const noexcept = default;

    template<typename U>
    friend constexpr bool operator==(
        const ReverseIterator<It>& lhs, const ReverseIterator<U>& rhs) noexcept {
        return lhs.operator->() == rhs.operator->();
    }

    template<typename U>
    friend constexpr auto operator<=>(
        const ReverseIterator<It>& lhs, const ReverseIterator<U>& rhs) noexcept {
        return lhs.operator->() <=> rhs.operator->();
    }

private:
    It m_current;
};
}  // namespace xme
