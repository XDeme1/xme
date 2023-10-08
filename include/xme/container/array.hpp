#pragma once
#include "concepts.hpp"
#include <cassert>
#include <algorithm>
#include <memory>
#include <xme/iterators/contiguous_iterator.hpp>
#include <xme/iterators/reverse_iterator.hpp>

namespace xme {
//! Array is a contigous container with dynamic size.
//! Random access is O(1).
//! push and pop from end is amortized O(1).
//! insert at the middle is O(n).
//! @param T the type of the stored element
//! @param Alloc must be an allocator that satisfies the Allocator concept
template<typename T, CAllocator Alloc = std::allocator<T>>
class Array {
private:
    using self = Array<T, Alloc>;

public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::Array must have a non-const and non-volatile T");
    static_assert(std::is_same_v<T, typename Alloc::value_type>,
                  "xme::Array must have the same T as its allocator");

    using allocator_type = Alloc;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = ContiguousIterator<T>;
    using const_iterator = ContiguousIterator<const T>;
    using reverse_iterator = xme::ReverseIterator<iterator>;
    using const_reverse_iterator = xme::ReverseIterator<const_iterator>;

    constexpr Array() noexcept = default;

    //! Allocates memory for N elements, but doesn't create any.
    explicit constexpr Array(size_type n) {
        m_data.begin = m_data.end = m_allocator.allocate(n);
        m_data.storage_end = m_data.begin + n;
    }

    //! Allocates and create N elements of the same value.
    constexpr Array(size_type n, const T& value) : Array(n) {
        try {
            for (std::size_t i = 0; i < n; ++i) {
                std::ranges::construct_at(m_data.end, value);
                ++m_data.end;
            }
        } catch (...) {
            std::ranges::destroy(*this);
            throw;
        }
    }

    constexpr Array(std::initializer_list<T> list) : Array(list.begin(), list.end()) {}

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr Array(Iter first, Sent last) : Array(std::ranges::distance(first, last)) {
        try {
            for (; first != last; ++first) {
                std::ranges::construct_at(m_data.end, *first);
                ++m_data.end;
            }
        } catch (...) {
            std::ranges::destroy(*this);
            throw;
        }
    }

    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
    explicit constexpr Array(R&& range)
        : Array(std::ranges::begin(range), std::ranges::end(range)) {}

    constexpr Array(const Array& other) : Array(other.begin(), other.end()) {}

    constexpr Array(Array&& other) noexcept : m_data(std::move(other.m_data)) {}

    constexpr ~Array() noexcept {
        std::ranges::destroy(*this);
        if(m_data.begin)
            m_allocator.deallocate(m_data.begin, capacity());
    }

    constexpr auto operator=(std::initializer_list<T> list) -> Array& {
        self tmp{list};
        std::ranges::swap(m_data, tmp.m_data);
        return *this;
    }

    constexpr auto operator=(const Array& other) -> Array& {
        self tmp{other};
        std::ranges::swap(m_data, tmp.m_data);
        return *this;
    }

    constexpr auto operator=(Array&& other) noexcept -> Array& {
        self tmp{std::move(other)};
        std::ranges::swap(m_data, tmp.m_data);
        return *this;
    }

    constexpr auto operator[](size_type index) noexcept -> reference {
        assert(index < size());
        return m_data.begin[index];
    }

    constexpr auto operator[](size_type index) const noexcept -> const_reference {
        assert(index < size());
        return m_data.begin[index];
    }

    constexpr auto data() noexcept -> pointer { return m_data.begin; }
    constexpr auto data() const noexcept -> const_pointer { return m_data.begin; } 

    constexpr auto begin() noexcept -> iterator { return m_data.begin; }
    constexpr auto end() noexcept -> iterator { return m_data.end; }

    constexpr auto begin() const noexcept -> const_iterator { return m_data.begin; }
    constexpr auto end() const noexcept -> const_iterator { return m_data.end; }

    constexpr auto cbegin() const noexcept -> const_iterator { return m_data.begin; }
    constexpr auto cend() const noexcept -> const_iterator { return m_data.end; }

    constexpr auto rbegin() noexcept -> reverse_iterator { return end(); }
    constexpr auto rend() noexcept -> reverse_iterator { return begin(); }

    constexpr auto rbegin() const noexcept -> const_reverse_iterator { return end(); }
    constexpr auto rend() const noexcept -> const_reverse_iterator { return begin(); }

    constexpr auto crbegin() const noexcept -> const_reverse_iterator { return cend(); }
    constexpr auto crend() const noexcept -> const_reverse_iterator { return cbegin(); }

    constexpr auto front() noexcept -> reference { return *begin(); }
    constexpr auto front() const noexcept -> const_reference { return *begin(); }

    constexpr auto back() noexcept -> reference { return *(end()-1); }
    constexpr auto back() const noexcept -> reference { return *(end()-1); }

    constexpr auto size() const noexcept -> size_type {
        return m_data.end - m_data.begin;
    }

    constexpr auto capacity() const noexcept -> size_type {
        return m_data.storage_end - m_data.begin;
    }

    constexpr bool isEmpty() const noexcept { return m_data.begin == m_data.end; }

    constexpr void clear() noexcept {
        if constexpr (!std::is_trivially_destructible_v<T>){
            std::ranges::destroy(*this);
        }
        m_data.end = m_data.begin;
    }

    //! Grows the Array capacity,
    //! If the argument is lower than the current capacity, nothing happens,
    constexpr void reserve(size_type n) {
        if(capacity() < n)
            growStorage(n);
    }

    //! Grows or shrinks the Array capacity.
    //! When growing, only allocates memory, doesn't create objects.
    constexpr void resize(size_type n) {
        if (capacity() < n)
            growStorage(n);
        else if (capacity() > n)
            shrinkStorage(n);
    }

    //! Inserts value in a specified position and returns the position.
    //! If the copy/move constructor throw, the state is unspecified.
    //! It is recommended to never throw on move construcor/assignment.
    template<std::convertible_to<T> U>
    constexpr auto insert(const_iterator pos, U&& value) -> iterator {
        pointer p = const_cast<pointer>(pos.operator->());
        if(size()+1 > capacity()) {
            self tmp(capacity() == 0 ? 1 : capacity()*2);
            const auto elements_before = std::ranges::distance(begin(), pos);
            // Must be constructed first, so if it throws we don't break the original array
            std::ranges::construct_at(tmp.m_data.begin+elements_before, std::forward<U>(value));

            std::move(cbegin(), pos, tmp.begin());
            std::move(pos, cend(), tmp.begin()+elements_before+1);
            tmp.m_data.end = tmp.m_data.begin+size()+1;
            std::ranges::swap(m_data, tmp.m_data);
            
            return begin()+elements_before;
        }
        
        std::move_backward(pos, cend(), end()+1);
        ++m_data.end;
        std::ranges::construct_at(p, std::forward<U>(value));
        return p;
    }

    template<std::convertible_to<T> U>
    constexpr void pushBack(U&& value) {
        emplaceBack(std::forward<U>(value));
    }

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr void pushBack(Iter first, Sent last) {
        std::size_t dist = std::ranges::distance(first, last);
        if(size()+dist > capacity()) {
            growStorage(capacity()+dist);
        }
        for(; first != last; ++first) {
            std::ranges::construct_at(m_data.end, *first);
            ++m_data.end;
        }
    }

    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
    constexpr void pushBack(R&& range) {
        pushBack(std::ranges::begin(range), std::ranges::end(range));
    }

    constexpr void popBack() {
        assert(size() > 0);
        std::ranges::destroy_at(--m_data.end);
    }

    template<typename... Args>
    constexpr auto emplaceBack(Args&&... args) -> reference {
        if(m_data.end == m_data.storage_end)
            growStorage(size() + std::max(size(), size_type(1)));
            
        std::ranges::construct_at(m_data.end++, std::forward<Args>(args)...);
        return back();
    }

private:
    constexpr void growStorage(std::size_t n) {
        const auto old_size = size();
        pointer new_begin = m_allocator.allocate(n);

        std::move(m_data.begin, m_data.end, new_begin);
        m_allocator.deallocate(m_data.begin, capacity());
        m_data.begin = new_begin;
        m_data.end = new_begin+old_size;
        m_data.storage_end = new_begin+n;
    }

    constexpr void shrinkStorage(std::size_t n) {
        const auto elements_to_move = std::min(size(), n);
        pointer new_begin = m_allocator.allocate(n);

        std::move(begin(), begin()+elements_to_move, new_begin);
        std::ranges::destroy(begin()+elements_to_move, end());
        m_allocator.deallocate(m_data.begin, capacity());
        m_data.begin = new_begin;
        m_data.end = new_begin+elements_to_move;
        m_data.storage_end = new_begin+n;
    }

private:
    struct ArrayData {
        constexpr ArrayData() noexcept = default;
        constexpr ArrayData(ArrayData&& other) noexcept
            : begin(other.begin), end(other.end), storage_end(other.storage_end) {
            other.begin = other.end = other.storage_end = nullptr;
        }

        constexpr auto operator=(ArrayData&& other) noexcept -> ArrayData& {
            std::ranges::swap(begin, other.begin);
            std::ranges::swap(end, other.end);
            std::ranges::swap(storage_end, other.storage_end);
            return *this;
        }

        T* begin = nullptr;
        T* end = nullptr;
        T* storage_end = nullptr;
    };

    ArrayData m_data;
    [[no_unique_address]] Alloc m_allocator;
};
} // namespace xme

namespace std {
template<typename T, typename Alloc>
class back_insert_iterator<xme::Array<T, Alloc>> {
    using self = back_insert_iterator<xme::Array<T, Alloc>>;

public:
    using container_type = xme::Array<T, Alloc>;
    using iterator_category = output_iterator_tag;

    explicit constexpr back_insert_iterator(container_type& c) noexcept
        : m_container(std::addressof(c)) {}

    constexpr auto operator=(const container_type::value_type& value) -> self& {
        m_container->pushBack(value);
        return *this;
    }

    constexpr auto operator=(container_type::value_type&& value) -> self& {
        m_container->pushBack(std::move(value));
        return *this;
    }

    // no-op
    constexpr auto operator*() noexcept -> self& { return *this; }
    // no-op
    constexpr auto operator++() noexcept -> self& { return *this; }
    // no-op
    constexpr auto operator++(int) noexcept -> self { return *this; }

protected:
    container_type* m_container;
};

template<typename T, typename Alloc>
class insert_iterator<xme::Array<T, Alloc>> {
    using self = insert_iterator<xme::Array<T, Alloc>>;
    using iter = std::ranges::iterator_t<xme::Array<T, Alloc>>;

public:
    using container_type = xme::Array<T, Alloc>;
    using iterator_category = output_iterator_tag;

    explicit constexpr insert_iterator(container_type& c, iter _iter) noexcept
        : m_container(std::addressof(c)), m_iter(_iter) {}

    constexpr auto operator=(const container_type::value_type& value) -> self& {
        m_iter = m_container->insert(m_iter, value);
        ++m_iter;
        return *this;
    }

    constexpr auto operator=(container_type::value_type&& value) -> self& {
        m_iter = m_container->insert(m_iter, std::move(value));
        ++m_iter;
        return *this;
    }

    // no-op
    constexpr auto operator*() noexcept -> self& { return *this; }
    // no-op
    constexpr auto operator++() noexcept -> self& { return *this; }
    // no-op
    constexpr auto operator++(int) noexcept -> self { return *this; }

protected:
    container_type* m_container;
    iter m_iter;
};
} // namespace std