#pragma once
#include <iterator>

namespace xme {
template<typename T>
struct ContiguousIterator {
private:
    using self = ContiguousIterator<T>;

public:
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
    using iterator_category = std::random_access_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

    template<typename>
    friend struct ContiguousIterator;

    constexpr ContiguousIterator() noexcept = default;

    constexpr ContiguousIterator(pointer p) noexcept : m_current(p) {}

    template<std::convertible_to<T> U>
        requires(std::is_const_v<T>)
    constexpr ContiguousIterator(const ContiguousIterator<U>& it) noexcept :
      m_current(it.m_current) {}

    constexpr auto operator->() const noexcept -> pointer { return m_current; }

    constexpr auto operator*() const noexcept -> reference { return *m_current; }

    constexpr auto operator++() noexcept -> self& {
        ++m_current;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> self { return self(m_current++); }

    constexpr auto operator--() noexcept -> self& {
        --m_current;
        return *this;
    }

    constexpr auto operator--(int) noexcept -> self { return self(m_current--); }

    constexpr auto operator+(difference_type n) const noexcept -> self {
        return self(m_current + n);
    }

    friend constexpr auto operator+(difference_type n, const self& it) noexcept -> self {
        return self(n + it.m_current);
    }

    constexpr auto operator-(difference_type n) const noexcept -> self {
        return self(m_current - n);
    }

    friend constexpr auto operator-(difference_type n, const self& it) noexcept -> self {
        return self(n - it.m_current);
    }

    constexpr auto operator-(const ContiguousIterator& it) const noexcept -> difference_type {
        return m_current - it.m_current;
    }

    constexpr auto operator+=(difference_type n) noexcept -> self& {
        m_current += n;
        return *this;
    }

    constexpr auto operator-=(difference_type n) noexcept -> self& {
        m_current -= n;
        return *this;
    }

    constexpr auto operator[](difference_type n) const noexcept -> reference {
        return m_current[n];
    }

    constexpr bool operator==(const self& rhs) const noexcept = default;

    constexpr auto operator<=>(const self& rhs) const noexcept = default;

private:
    pointer m_current = nullptr;
};
}  // namespace xme
