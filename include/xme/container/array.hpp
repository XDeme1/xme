#pragma once
#include "concepts.hpp"
#include <algorithm>
#include <cassert>
#include <memory>
#include <xme/core/iterators/reverse_iterator.hpp>
#include <xme/setup.hpp>
#include <xme/ranges/uninitialized.hpp>
#include <xme/ranges/destroy.hpp>

namespace xme {
//! Array is a contigous container with dynamic size.
//! @param T the type of the stored element
//! @param Alloc must be an allocator that satisfies the Allocator concept
template<typename T, CAllocator Alloc = std::allocator<T>>
class Array {
private:
    using alloc_traits = std::allocator_traits<Alloc>;

    template<bool Const>
    class Iterator;

public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::Array must have a non-const and non-volatile T");
    static_assert(std::is_same_v<T, typename Alloc::value_type>,
                  "xme::Array must have the same T as its allocator");

    using allocator_type         = Alloc;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using value_type             = T;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;
    using iterator               = Iterator<false>;
    using const_iterator         = Iterator<true>;
    using reverse_iterator       = xme::ReverseIterator<iterator>;
    using const_reverse_iterator = xme::ReverseIterator<const_iterator>;

    constexpr Array() noexcept = default;

    constexpr Array(const Array& other) : Array(other.begin(), other.end(), other.m_allocator) {}

    constexpr Array(Array&& other) noexcept :
      m_data(std::move(other.m_data)), m_allocator(std::move(other.m_allocator)) {}

    explicit constexpr Array(const allocator_type& alloc) noexcept : m_allocator(alloc) {}

    //! Allocates memory for N elements, but doesn't create any.
    explicit constexpr Array(size_type n, const allocator_type& alloc = allocator_type()) :
      m_allocator(alloc) {
        m_data.begin = m_data.end = m_allocator.allocate(n);
        m_data.storage_end        = m_data.begin + n;
    }

    //! Allocates and create N elements of the same value.
    constexpr Array(size_type n, const T& value, const allocator_type& alloc = allocator_type()) :
      Array(n, alloc) {
        m_data.end = ranges::uninitialized_fill_n_a(m_data.begin, n, value, m_allocator);
    }

    constexpr Array(std::initializer_list<T> list, const allocator_type& alloc = allocator_type()) :
      Array(list.begin(), list.end(), alloc) {}

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr Array(Iter first, Sent last, const allocator_type& alloc = allocator_type()) :
      Array(std::ranges::distance(first, last), alloc) {
        auto&& [_, out] = xme::ranges::uninitialized_copy_a(
          first, last, m_data.begin, m_data.storage_end, m_allocator);
        m_data.end = out;
    }

    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
                && (!std::is_same_v<Array, std::decay_t<R>>)
    explicit constexpr Array(R&& range, const allocator_type& alloc = allocator_type()) :
      Array(std::ranges::begin(range), std::ranges::end(range), alloc) {}

    constexpr ~Array() noexcept {
        ranges::destroy_a(*this, m_allocator);
        if(m_data.begin)
            m_allocator.deallocate(m_data.begin, capacity());
    }

    constexpr auto operator=(const Array& other) -> Array& {
        Array(other).swap(*this);
        return *this;
    }

    constexpr auto operator=(Array&& other) noexcept(noexcept(this->swap(other))) -> Array& {
        Array(std::move(other)).swap(*this);
        return *this;
    }

    constexpr auto operator=(std::initializer_list<T> list) -> Array& {
        Array(list).swap(*this);
        return *this;
    }

    [[nodiscard]]
    constexpr auto operator[](size_type index) noexcept -> reference {
        assert(index < size());
        return m_data.begin[index];
    }

    [[nodiscard]]
    constexpr auto operator[](size_type index) const noexcept -> const_reference {
        assert(index < size());
        return m_data.begin[index];
    }

    [[nodiscard]]
    constexpr auto data() noexcept -> pointer {
        return m_data.begin;
    }

    [[nodiscard]]
    constexpr auto data() const noexcept -> const_pointer {
        return m_data.begin;
    }

    [[nodiscard]]
    constexpr auto begin() noexcept -> iterator {
        return m_data.begin;
    }

    [[nodiscard]]
    constexpr auto end() noexcept -> iterator {
        return m_data.end;
    }

    [[nodiscard]]
    constexpr auto begin() const noexcept -> const_iterator {
        return m_data.begin;
    }

    [[nodiscard]]
    constexpr auto end() const noexcept -> const_iterator {
        return m_data.end;
    }

    [[nodiscard]]
    constexpr auto cbegin() const noexcept -> const_iterator {
        return m_data.begin;
    }

    [[nodiscard]]
    constexpr auto cend() const noexcept -> const_iterator {
        return m_data.end;
    }

    [[nodiscard]]
    constexpr auto rbegin() noexcept -> reverse_iterator {
        return end();
    }

    [[nodiscard]]
    constexpr auto rend() noexcept -> reverse_iterator {
        return begin();
    }

    [[nodiscard]]
    constexpr auto rbegin() const noexcept -> const_reverse_iterator {
        return end();
    }

    [[nodiscard]]
    constexpr auto rend() const noexcept -> const_reverse_iterator {
        return begin();
    }

    [[nodiscard]]
    constexpr auto crbegin() const noexcept -> const_reverse_iterator {
        return cend();
    }

    [[nodiscard]]
    constexpr auto crend() const noexcept -> const_reverse_iterator {
        return cbegin();
    }

    [[nodiscard]]
    constexpr auto front() noexcept -> reference {
        return *begin();
    }

    [[nodiscard]]
    constexpr auto front() const noexcept -> const_reference {
        return *begin();
    }

    [[nodiscard]]
    constexpr auto back() noexcept -> reference {
        return *(end() - 1);
    }

    [[nodiscard]]
    constexpr auto back() const noexcept -> const_reference {
        return *(end() - 1);
    }

    //! @returns the amount of elements currently in the array.
    [[nodiscard]]
    constexpr auto size() const noexcept -> size_type {
        return m_data.end - m_data.begin;
    }

    //! @returns the amount of elements the container can hold without a resize
    [[nodiscard]]
    constexpr auto capacity() const noexcept -> size_type {
        return m_data.storage_end - m_data.begin;
    }

    //! Checks if the underlying storage is empty
    [[nodiscard]]
    constexpr bool empty() const noexcept {
        return m_data.begin == m_data.end;
    }

    constexpr void swap(Array& other) noexcept {
        std::ranges::swap(m_data, other.m_data);
        if constexpr(alloc_traits::propagate_on_container_swap::value)
            std::ranges::swap(m_allocator, other.m_allocator);
        else
            static_assert(alloc_traits::is_always_equal::value);
    }

    //! Erases every element, leaving the array empty while keeping its capacity.
    constexpr void clear() noexcept {
        ranges::destroy_a(*this, m_allocator);
        m_data.end = m_data.begin;
    }

    //! Grows the Array capacity,
    //! If the argument is lower than the current capacity, nothing happens,
    constexpr void reserve(size_type n) {
        if(capacity() < n)
            grow_storage(n);
    }

    //! Grows or shrinks the Array capacity.
    //! When growing, only allocates memory, doesn't create objects.
    constexpr void resize(size_type n) {
        if(capacity() < n)
            grow_storage(n);
        else if(capacity() > n)
            shrink_storage(n);
    }

    //! Inserts value in a specified position.
    //! If the copy/move constructor throw, the state is unspecified.
    //! It is recommended to never throw on move construcor/assignment.
    //! @returns an iterator to the newly inserted element.
    template<std::convertible_to<T> U>
    constexpr auto insert(const_iterator pos, U&& value) -> iterator {
        auto p = const_cast<pointer>(pos.operator->());
        if(pos == cend()) {
            emplace_back(std::forward<U>(value));
            return end() - 1;
        }
        else if(m_data.end == m_data.storage_end) {
            return realloc_insert(p, std::forward<U>(value));
        }
        alloc_traits::construct(m_allocator, m_data.end, std::move(*(m_data.end - 1)));
        ++m_data.end;
        std::move_backward(p, m_data.end - 2, m_data.end - 1);
        *p = std::forward<U>(value);
        return p;
    }

    //! Inserts [first, last) in a specified position..
    //! If the copy/move constructor throw, the state is unspecified.
    //! It is recommended to never throw on move construcor/assignment.
    //! @returns an iterator to the first inserted element.
    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr auto insert(const_iterator pos, Iter first, Sent last) -> iterator {
        auto p             = const_cast<pointer>(pos.operator->());
        size_type elements = std::ranges::distance(first, last);
        if(size() + elements > capacity()) {
            Array tmp(capacity() == 0 ? elements : capacity() + elements);
            size_type elements_before = std::ranges::distance(begin(), pos);

            // Must be constructed first, so if it throws we don't break the original
            // array
            for(std::size_t n = 0; first != last; ++first, ++n)
                alloc_traits::construct(
                  m_allocator, tmp.m_data.begin + elements_before + n, *first);

            std::ranges::move(cbegin(), pos, tmp.begin());
            std::ranges::move(pos, cend(), tmp.begin() + elements_before + elements);
            tmp.m_data.end = tmp.m_data.begin + size() + elements;
            std::ranges::swap(m_data, tmp.m_data);

            return begin() + elements_before;
        }

        std::move_backward(pos, cend(), end() + elements);
        m_data.end += elements;
        for(std::size_t n = 0; first != last; ++first, ++n)
            alloc_traits::construct(m_allocator, p + n, *first);
        return p;
    }

    //! Inserts [begin(range), end(range)) in a specified position..
    //! If the copy/move constructor throw, the state is unspecified.
    //! It is recommended to never throw on move construcor/assignment.
    //! @returns an iterator to the first inserted element.
    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
    constexpr auto insert(const_iterator pos, R&& range) -> iterator {
        return insert(pos, std::ranges::begin(range), std::ranges::end(range));
    }

    //! Pushes a `value` to the end of the array.
    template<std::convertible_to<T> U>
    constexpr void push_back(U&& value) {
        emplace_back(std::forward<U>(value));
    }

    //! Pushes [first, last) to the end of the array.
    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr void push_back(Iter first, Sent last) {
        size_type new_capacity = size() + std::ranges::distance(first, last);
        if(new_capacity > capacity()) {
            grow_storage(new_capacity);
        }
        for(; first != last; ++first) {
            alloc_traits::construct(m_allocator, m_data.end, *first);
            ++m_data.end;
        }
    }

    //! Pushes a range [begin(range), end(range)) to the end of the array.
    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
    constexpr void push_back(R&& range) {
        push_back(std::ranges::begin(range), std::ranges::end(range));
    }

    //! Destroys the last element in the array.
    constexpr void pop_back() {
        assert(size() > 0);
        --m_data.end;
        ranges::destroy_at_a(m_data.end, m_allocator);
    }

    //! @returns a reference to the newly inserted element.
    template<typename... Args>
    constexpr auto emplace_back(Args&&... args) -> reference {
        if(m_data.end == m_data.storage_end)
            grow_storage(size() + std::max(size(), size_type(1)));

        alloc_traits::construct(m_allocator, m_data.end, std::forward<Args>(args)...);
        ++m_data.end;
        return back();
    }

    //! Erases the element in pos
    //! @returns an iterator pointing to the element after it
    constexpr auto erase(const_iterator pos) -> iterator {
        auto p = const_cast<pointer>(pos.operator->());
        ranges::destroy_at_a(p, m_allocator);
        std::ranges::move(std::ranges::next(pos), cend(), p);
        --m_data.end;
        return p;
    }

    //! Erases the element in [first, last)
    //! @returns an iterator pointing to the element at `last`
    constexpr auto erase(const_iterator first, const_iterator last) -> iterator {
        auto p             = const_cast<pointer>(first.operator->());
        size_type elements = std::ranges::distance(first, last);
        ranges::destroy_n_a(p, elements, m_allocator);
        std::ranges::move(first + elements, cend(), p);
        m_data.end -= elements;
        return p;
    }

private:
    constexpr void grow_storage(size_type n) {
        const auto old_size = size();
        pointer new_begin   = m_allocator.allocate(n);

        std::ranges::move(*this, new_begin);
        if(m_data.begin)
            m_allocator.deallocate(m_data.begin, capacity());
        m_data.begin       = new_begin;
        m_data.end         = new_begin + old_size;
        m_data.storage_end = new_begin + n;
    }

    constexpr void shrink_storage(size_type n) {
        size_type elements_to_move = std::min(size(), n);
        pointer new_begin          = m_allocator.allocate(n);

        std::ranges::move(begin(), begin() + elements_to_move, new_begin);
        ranges::destroy_a(m_data.begin + elements_to_move, m_data.end, m_allocator);
        m_allocator.deallocate(m_data.begin, capacity());
        m_data.begin       = new_begin;
        m_data.end         = new_begin + elements_to_move;
        m_data.storage_end = new_begin + n;
    }

    template<typename... Args>
    constexpr auto realloc_insert(iterator pos, Args&&... args) -> iterator {
        const size_type elements_before = pos - begin();
        const size_type new_size        = size() + std::max(size(), size_type(1));
        const size_type curr_size       = size();
        pointer new_start               = m_allocator.allocate(new_size);
        try {
            alloc_traits::construct(
              m_allocator, new_start + elements_before, std::forward<Args>(args)...);
            std::ranges::move(begin(), pos, new_start);
            std::ranges::move(pos, end(), new_start + elements_before + 1);
        }
        catch(...) {
            ranges::destroy_at_a(new_start + elements_before, m_allocator);
            m_allocator.deallocate(new_start, new_size);
            throw;
        }
        m_allocator.deallocate(m_data.begin, capacity());
        m_data.begin       = new_start;
        m_data.end         = new_start + (curr_size + 1);
        m_data.storage_end = new_start + new_size;
        return begin() + elements_before;
    }

private:
    struct ArrayData {
        constexpr ArrayData() noexcept = default;
        constexpr ArrayData(ArrayData&& other) noexcept :
          begin(other.begin), end(other.end), storage_end(other.storage_end) {
            other.begin = other.end = other.storage_end = nullptr;
        }

        constexpr auto operator=(ArrayData&& other) noexcept -> ArrayData& {
            std::ranges::swap(begin, other.begin);
            std::ranges::swap(end, other.end);
            std::ranges::swap(storage_end, other.storage_end);
            return *this;
        }

        T* begin       = nullptr;
        T* end         = nullptr;
        T* storage_end = nullptr;
    };

    ArrayData m_data;
    [[no_unique_address]]
    Alloc m_allocator;
};

template<typename T, CAllocator Alloc>
template<bool Const>
class Array<T, Alloc>::Iterator {
public:
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using reference         = T&;
    using pointer           = T*;
    using iterator_category = std::random_access_iterator_tag;
    using iterator_concept  = std::contiguous_iterator_tag;

    template<bool>
    friend class Iterator;

    constexpr Iterator() noexcept = default;

    constexpr Iterator(pointer p) noexcept : m_cursor(p) {}

    constexpr Iterator(const Iterator<!Const>& it) noexcept
        requires(Const)
      : m_cursor(it.m_cursor) {}

    constexpr auto operator->() const noexcept -> pointer { return m_cursor; }

    constexpr auto operator*() const noexcept -> reference { return *m_cursor; }

    constexpr auto operator++() noexcept -> Iterator& {
        ++m_cursor;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> Iterator { return m_cursor++; }

    constexpr auto operator--() noexcept -> Iterator& {
        --m_cursor;
        return *this;
    }

    constexpr auto operator--(int) noexcept -> Iterator { return m_cursor--; }

    constexpr auto operator+(difference_type n) const noexcept -> Iterator { return m_cursor + n; }

    friend constexpr auto operator+(difference_type n, const Iterator& it) noexcept -> Iterator {
        return n + it.m_cursor;
    }

    constexpr auto operator-(difference_type n) const noexcept -> Iterator { return m_cursor - n; }

    friend constexpr auto operator-(difference_type n, const Iterator& it) noexcept -> Iterator {
        return n - it.m_cursor;
    }

    constexpr auto operator-(const Iterator& it) const noexcept -> difference_type {
        return m_cursor - it.m_cursor;
    }

    constexpr auto operator+=(difference_type n) noexcept -> Iterator& {
        m_cursor += n;
        return *this;
    }

    constexpr auto operator-=(difference_type n) noexcept -> Iterator& {
        m_cursor -= n;
        return *this;
    }

    constexpr auto operator[](difference_type n) const noexcept -> reference { return m_cursor[n]; }

    constexpr bool operator==(const Iterator& rhs) const noexcept = default;

    constexpr auto operator<=>(const Iterator& rhs) const noexcept = default;

private:
    pointer m_cursor = nullptr;
};
}  // namespace xme
