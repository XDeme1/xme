#pragma once
#include <iterator>

namespace xme::detail {
template<typename T>
struct ContinuousIterator {
private:
    using self = ContinuousIterator<T>;

public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::contiguous_iterator_tag;

    constexpr ContinuousIterator() noexcept = default;

    template<std::convertible_to<T> U>
    constexpr ContinuousIterator(U* ptr) noexcept : current(ptr) {}

    template<std::convertible_to<T> U>
        requires(std::is_const_v<T>)
    constexpr ContinuousIterator(const ContinuousIterator<U>& it) noexcept
        : current(it.operator->()) {}

    constexpr auto operator->() const noexcept -> pointer { return current; }

    constexpr auto operator*() const noexcept -> reference { return *current; }

    constexpr auto operator+(std::ptrdiff_t n) const noexcept -> self {
        return current + n;
    }

    constexpr auto operator-(std::ptrdiff_t n) const noexcept -> self {
        return current - n;
    }

    friend constexpr auto operator+(std::ptrdiff_t n, const self& it) noexcept -> self {
        return n + it.current;
    }

    friend constexpr auto operator-(std::ptrdiff_t n, const self& it) noexcept -> self {
        return n - it.current;
    }

    template<typename U1, typename U2>
    friend constexpr auto operator+(const ContinuousIterator<U1>& lhs,
                                    const ContinuousIterator<U2>& rhs) noexcept -> self {
        return lhs.current + rhs.current;
    }

    template<typename U1, typename U2>
    friend constexpr auto operator-(const ContinuousIterator<U1>& lhs,
                                    const ContinuousIterator<U2>& rhs) noexcept -> self {
        return lhs.current - rhs.current;
    }

    constexpr auto operator++() noexcept -> self& {
        ++current;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> self {
        self tmp{*this};
        ++current;
        return tmp;
    }

    constexpr auto operator--() noexcept -> self& {
        --current;
        return *this;
    }

    constexpr auto operator--(int) noexcept -> self {
        self tmp{*this};
        --current;
        return tmp;
    }

    constexpr auto operator+=(std::ptrdiff_t n) noexcept -> self& {
        current += n;
        return *this;
    }

    constexpr auto operator-=(std::ptrdiff_t n) noexcept -> self& {
        current -= n;
        return *this;
    }

    constexpr auto operator[](std::size_t n) const noexcept -> reference {
        return current[n];
    }

    constexpr bool operator==(const self& rhs) const noexcept = default;

    constexpr auto operator<=>(const self& rhs) const noexcept = default;

private:
    pointer current = nullptr;
};
} // namespace xme::detail