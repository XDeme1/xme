#pragma once
#include <cassert>
#include <cstddef>
#include <ranges>
#include <xme/iterators/contiguous_iterator.hpp>
#include <xme/iterators/reverse_iterator.hpp>

namespace xme {
template<typename T, std::size_t Size>
class ArrayView;

namespace detail {
template<std::size_t S>
struct Extent {
    constexpr Extent() noexcept = default;
    constexpr Extent(std::size_t) noexcept {}

    constexpr auto size() const noexcept -> std::size_t { return S; }
};

template<>
struct Extent<static_cast<std::size_t>(-1)> {
    constexpr Extent() noexcept = default;

    constexpr Extent(std::size_t _size) noexcept : s(_size) {}

    constexpr auto size() const noexcept -> std::size_t { return s; }
    std::size_t s = 0;
};

template<typename U>
constexpr bool is_std_array = false;
template<typename U, std::size_t Lenght>
constexpr bool is_std_array<std::array<U, Lenght>> = true;

template<typename U>
constexpr bool is_array_view = false;
template<typename U, std::size_t N>
constexpr bool is_array_view<xme::ArrayView<U, N>> = true;
} // namespace detail
} // namespace xme

namespace xme {

template<typename T, std::size_t Size = static_cast<std::size_t>(-1)>
class ArrayView {
private:
    static constexpr std::size_t dynamic_size = -1;

public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = ContiguousIterator<T>;
    using const_iterator = ContiguousIterator<const T>;
    using reverse_iterator = ReverseIterator<iterator>;
    using const_reverse_iterator = ReverseIterator<const_iterator>;

    constexpr ArrayView() noexcept
        requires(Size == dynamic_size || Size == 0)
    = default;

    constexpr ArrayView(const ArrayView&) noexcept = default;

    template<std::contiguous_iterator Iter>
    constexpr ArrayView(Iter it, std::size_t size) noexcept
        : m_view(std::to_address(it)), m_size(size) {
        if constexpr (Size != dynamic_size)
            assert(size == Size);
    }

    template<std::contiguous_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr ArrayView(Iter first, Sent last) noexcept
        : ArrayView(first, std::ranges::distance(first, last)) {}

    template<std::ranges::contiguous_range R>
        requires(std::ranges::sized_range<R>) && (std::ranges::borrowed_range<R>) &&
                (!detail::is_std_array<std::remove_cvref_t<R>>) &&
                (!std::is_array_v<std::remove_cvref_t<R>>) &&
                (!detail::is_array_view<std::remove_cvref_t<R>>)
    constexpr ArrayView(R&& range) noexcept
        : ArrayView(std::ranges::data(range), std::ranges::size(range)) {}

    template<std::size_t Lenght>
        requires(Size == dynamic_size || Size == Lenght)
    constexpr ArrayView(T (&arr)[Lenght]) noexcept
        : ArrayView(static_cast<pointer>(arr), Lenght) {}

    template<typename U, std::size_t Lenght>
        requires(Size == dynamic_size || Size == Lenght)
    constexpr ArrayView(std::array<U, Lenght>& arr) noexcept
        : ArrayView(static_cast<pointer>(arr.data()), Lenght) {}

    template<typename U, std::size_t Lenght>
        requires(Size == dynamic_size || Size == Lenght)
    constexpr ArrayView(const std::array<U, Lenght>& arr) noexcept
        : ArrayView(static_cast<pointer>(arr.data()), Lenght) {}

    constexpr auto operator[](size_type i) noexcept -> reference {
        assert(i < size());
        return m_view[i];
    }

    constexpr auto operator[](size_type i) const noexcept -> const_reference {
        assert(i < size());
        return m_view[i];
    }

    constexpr auto data() noexcept -> pointer { return m_view; }
    constexpr auto data() const noexcept -> const_pointer { return m_view; }

    constexpr auto begin() noexcept -> iterator { return m_view; }
    constexpr auto end() noexcept -> iterator { return m_view + size(); }

    constexpr auto begin() const noexcept -> const_iterator { return m_view; }
    constexpr auto end() const noexcept -> const_iterator { return m_view + size(); }

    constexpr auto cbegin() const noexcept -> const_iterator { return m_view; }
    constexpr auto cend() const noexcept -> const_iterator { return m_view + size(); }

    constexpr auto rbegin() noexcept -> reverse_iterator { return end(); }
    constexpr auto rend() noexcept -> reverse_iterator { return begin(); }

    constexpr auto rbegin() const noexcept -> const_reverse_iterator { return end(); }
    constexpr auto rend() const noexcept -> const_reverse_iterator { return begin(); }

    constexpr auto crbegin() const noexcept -> const_reverse_iterator { return end(); }
    constexpr auto crend() const noexcept -> const_reverse_iterator { return begin(); }

    constexpr auto front() noexcept -> reference { return *m_view; }
    constexpr auto back() noexcept -> reference { return m_view[size() - 1]; }

    constexpr auto front() const noexcept -> const_reference { return *m_view; }
    constexpr auto back() const noexcept -> const_reference { return m_view[size() - 1]; }

    constexpr auto size() const noexcept -> size_type { return m_size.size(); }

    template<std::size_t Offset, std::size_t Count>
    constexpr auto subview() const noexcept -> ArrayView<T, Count> {
        if constexpr(Size == dynamic_size)
            assert(Count + Offset <= size());
        else
            static_assert(Count + Offset <= Size);
        return ArrayView<T, Count>(m_view+Offset, Count);
    }

    constexpr auto subview(size_type offset, size_type count) const noexcept
        -> ArrayView<T, dynamic_size> {
        assert(count + offset <= size());
        return ArrayView<T, dynamic_size>(m_view + offset, count);
    }

    template<std::size_t Count>
    constexpr auto first() const noexcept -> ArrayView<T, Count> {
        if constexpr (Size == dynamic_size)
            assert(Count <= size());
        else
            static_assert(Count <= Size);
        return ArrayView<T, Count>(m_view, Count);
    }

    constexpr auto first(size_type count) const noexcept -> ArrayView<T, dynamic_size> {
        assert(count <= size());
        return ArrayView<T, dynamic_size>(m_view, count);
    }

    template<std::size_t Count>
    constexpr auto last() const noexcept -> ArrayView<T, Count> {
        if constexpr (Size == dynamic_size)
            assert(Count <= size());
        else
            static_assert(Count <= Size);
        return ArrayView<T, Count>(m_view + (size() - Count), Count);
    }

    constexpr auto last(size_type count) const noexcept -> ArrayView<T, dynamic_size> {
        assert(count <= size());
        return ArrayView<T, dynamic_size>(m_view + (size() - count), count);
    }

private:
    T* m_view = nullptr;
    [[no_unique_address]] detail::Extent<static_cast<std::size_t>(Size)> m_size;
};
} // namespace xme