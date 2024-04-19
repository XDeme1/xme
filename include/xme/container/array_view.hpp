#pragma once
#include "xme/container/icontainer.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <xme/core/iterators/reverse_iterator.hpp>

namespace xme {
template<typename T, std::size_t Size>
class ArrayView;

namespace detail {
template<std::size_t S>
struct Extent {
    constexpr Extent() noexcept = default;
    constexpr Extent(std::size_t) noexcept {}

    [[nodiscard]]
    constexpr auto size() const noexcept -> std::size_t {
        return S;
    }
};

template<>
struct Extent<static_cast<std::size_t>(-1)> {
    constexpr Extent() noexcept = default;

    constexpr Extent(std::size_t _size) noexcept : s(_size) {}

    [[nodiscard]]
    constexpr auto size() const noexcept -> std::size_t {
        return s;
    }
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
}  // namespace detail
}  // namespace xme

namespace xme {
//! ArrayView is a view to a contigous container.
//! ArrayView is cheap to copy.
//! Uses 8 bytes when the size is not dynamic and 16 otherwise.
//! @param T the type of element to view in a container
//! @param Size Specifies the size of the container
template<typename T, std::size_t Size = static_cast<std::size_t>(-1)>
class ArrayView : public IContainer<ArrayView<T, Size>> {
private:
    static constexpr std::size_t dynamic_size = -1;

public:
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using value_type             = T;
    using pointer                = T*;
    using const_pointer          = const T*;
    using reference              = T&;
    using const_reference        = const T&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using reverse_iterator       = ReverseIterator<iterator>;
    using const_reverse_iterator = ReverseIterator<const_iterator>;

    //! ArrayView is only default constructible if size is not known
    constexpr ArrayView() noexcept
        requires(Size == dynamic_size || Size == 0)
    = default;

    //! Creates an ArrayView pointing to an iterator up to it + size
    template<std::contiguous_iterator Iter>
    constexpr ArrayView(Iter it, std::size_t size) noexcept :
      m_view(std::to_address(it)), m_size(size) {
        if constexpr(Size != dynamic_size)
            assert(size == Size);
    }

    //! Creates an ArrayView pointing to first, up to first + distance(first,
    //! last)
    template<std::contiguous_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr ArrayView(Iter first, Sent last) noexcept :
      ArrayView(first, std::ranges::distance(first, last)) {}

    //! Create an ArrayView pointing to begin(range) up to end(range)
    template<std::ranges::contiguous_range R>
        requires(std::ranges::sized_range<R>) && (std::ranges::borrowed_range<R>)
                && (!detail::is_std_array<std::remove_cvref_t<R>>)
                && (!std::is_array_v<std::remove_cvref_t<R>>)
                && (!detail::is_array_view<std::remove_cvref_t<R>>)
    constexpr ArrayView(R&& range) noexcept :
      ArrayView(std::ranges::data(range), std::ranges::size(range)) {}

    //! Create an ArrayView pointing to a C-Style array
    template<std::size_t Lenght>
        requires(Size == dynamic_size || Size == Lenght)
    constexpr ArrayView(std::type_identity_t<T> (&arr)[Lenght]) noexcept :
      ArrayView(static_cast<pointer>(arr), Lenght) {}

    //! Create an ArrayView pointing to a C++-Style array
    template<typename U, std::size_t Lenght>
        requires(Size == dynamic_size || Size == Lenght)
    constexpr ArrayView(std::array<U, Lenght>& arr) noexcept :
      ArrayView(static_cast<pointer>(arr.data()), Lenght) {}

    //! Create an ArrayView pointing to a const C++-Style array
    //! Do not pass a temporary array, a view does not extends the lifetime of the
    //! array
    template<typename U, std::size_t Lenght>
        requires(Size == dynamic_size || Size == Lenght)
    constexpr ArrayView(const std::array<U, Lenght>& arr) noexcept :
      ArrayView(static_cast<pointer>(arr.data()), Lenght) {}

    //! Returns an iterator to the first element of the view
    [[nodiscard]]
    constexpr auto begin() noexcept -> iterator {
        return m_view;
    }

    //! Returns an iterator to the first element of the view
    [[nodiscard]]
    constexpr auto begin() const noexcept -> const_iterator {
        return m_view;
    }

    //! Returns an iterator to one past the last element of the view
    [[nodiscard]]
    constexpr auto end() noexcept -> iterator {
        return m_view + size();
    }

    //! Returns an iterator to one past the last element of the view
    [[nodiscard]]
    constexpr auto end() const noexcept -> const_iterator {
        return m_view + size();
    }

    //! Returns the size of the view
    [[nodiscard]]
    constexpr auto size() const noexcept -> size_type {
        return m_size.size();
    }

    //! Returns the size in bytes of the view
    [[nodiscard]]
    constexpr auto size_bytes() const noexcept -> size_type {
        return m_size.size() * sizeof(T);
    }

    //! Creates a new ArrayView containing a part of the view
    template<std::size_t Offset, std::size_t Count>
    [[nodiscard]]
    constexpr auto subview() const noexcept -> ArrayView<T, Count> {
        if constexpr(Size == dynamic_size)
            assert(Count + Offset <= size());
        else
            static_assert(Count + Offset <= Size);
        return ArrayView<T, Count>(m_view + Offset, Count);
    }

    //! Creates a new ArrayView containing a part of the view
    [[nodiscard]]
    constexpr auto subview(size_type offset,
                           size_type count) const noexcept -> ArrayView<T, dynamic_size> {
        assert(count + offset <= size());
        return ArrayView<T, dynamic_size>(m_view + offset, count);
    }

    //! Creates a new ArrayView containing the first N elements
    template<std::size_t Count>
    constexpr auto first() const noexcept -> ArrayView<T, Count> {
        if constexpr(Size == dynamic_size)
            assert(Count <= size());
        else
            static_assert(Count <= Size);
        return ArrayView<T, Count>(m_view, Count);
    }

    //! Creates a new ArrayView containing the first N elements
    constexpr auto first(size_type count) const noexcept -> ArrayView<T, dynamic_size> {
        assert(count <= size());
        return ArrayView<T, dynamic_size>(m_view, count);
    }

    //! Creates a new ArrayView containing the last N elements
    template<std::size_t Count>
    constexpr auto last() const noexcept -> ArrayView<T, Count> {
        if constexpr(Size == dynamic_size)
            assert(Count <= size());
        else
            static_assert(Count <= Size);
        return ArrayView<T, Count>(m_view + (size() - Count), Count);
    }

    //! Creates a new ArrayView containing the last N elements
    constexpr auto last(size_type count) const noexcept -> ArrayView<T, dynamic_size> {
        assert(count <= size());
        return ArrayView<T, dynamic_size>(m_view + (size() - count), count);
    }

private:
    T* m_view = nullptr;
    [[no_unique_address]]
    detail::Extent<Size> m_size;
};

template<typename T, std::size_t N>
ArrayView(T (&)[N]) -> ArrayView<T, N>;

template<typename T, std::size_t N>
ArrayView(std::array<T, N>&) -> ArrayView<T, N>;

template<typename T, std::size_t N>
ArrayView(const std::array<T, N>&) -> ArrayView<const T, N>;

template<std::contiguous_iterator Iter, typename End>
ArrayView(Iter, End) -> ArrayView<std::remove_reference_t<std::iter_reference_t<Iter>>>;

template<std::ranges::contiguous_range R>
ArrayView(R&&) -> ArrayView<std::remove_reference_t<std::ranges::range_reference_t<R>>>;

//! Creates a readonly byte ArrayView of any ArrayView
template<typename T, std::size_t Size>
constexpr auto as_bytes(ArrayView<T, Size> view) noexcept
  -> ArrayView<const std::byte, Size == -1 ? -1 : sizeof(T) * Size> {
    auto data                  = reinterpret_cast<const std::byte*>(view.data());
    auto byteSize              = view.size_bytes();
    constexpr std::size_t size = Size == -1 ? -1 : sizeof(T) * Size;
    return ArrayView<const std::byte, size>(data, byteSize);
}

//! Creates a writable byte ArrayView of any ArrayView
template<typename T, std::size_t Size>
    requires(!std::is_const_v<T>)
constexpr auto as_writable_bytes(ArrayView<T, Size> view) noexcept
  -> ArrayView<std::byte, Size == -1 ? -1 : sizeof(T) * Size> {
    auto data                  = reinterpret_cast<std::byte*>(view.data());
    auto byteSize              = view.size_bytes();
    constexpr std::size_t size = Size == -1 ? -1 : sizeof(T) * Size;
    return ArrayView<std::byte, size>(data, byteSize);
}
}  // namespace xme

namespace std::ranges {
template<typename T, std::size_t S>
constexpr bool enable_borrowed_range<xme::ArrayView<T, S>> = true;

template<typename T, std::size_t S>
constexpr bool enable_view<xme::ArrayView<T, S>> = true;
}  // namespace std::ranges
