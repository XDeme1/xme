#pragma once
#include "../../../private/container/array_base.hpp"
#include "concepts.hpp"
#include <memory>

namespace xme {
template<typename T, CStatelessAllocator Alloc = std::allocator<T>>
class Array {
private:
    using self = Array<T, Alloc>;

public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::Array must have a non-const and non-volatile T");
    static_assert(std::is_same_v<T, typename Alloc::value_type>,
                  "xme::Array must have the same T as its allocator");

    using allocator_type = Alloc;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = detail::ContinuousIterator<T>;
    using const_iterator = detail::ContinuousIterator<const T>;

    constexpr Array() noexcept = default;

    explicit constexpr Array(size_type n) {
        m_data.begin = m_data.end = m_allocator.allocate(n);
        m_data.storage_end = m_data.begin + n;
    }

    constexpr Array(size_type n, const T& value) : Array(n) {
        try {
            for (std::size_t i = 0; i < n; ++i) {
                std::ranges::construct_at(m_data.end, value);
                ++m_data.end;
            }
        } catch (...) {
            clear();
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
            clear();
            throw;
        }
    }

    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
    explicit constexpr Array(R&& range)
        : Array(std::ranges::begin(range), std::ranges::end(range)) {}

    constexpr Array(const Array& other) : Array(other.begin(), other.end()) {}

    constexpr Array(Array&& other) noexcept { std::ranges::swap(m_data, other.m_data); }

    constexpr ~Array() noexcept {
        clear();
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
        self tmp;
        std::ranges::swap(m_data, other.m_data);
        std::ranges::swap(tmp.m_data, other.m_data);
        return *this;
    }

    constexpr auto operator[](size_type index) noexcept -> reference {
        return m_data.begin[index];
    }

    constexpr auto operator[](size_type index) const noexcept -> const_reference {
        return m_data.begin[index];
    }

    constexpr auto begin() noexcept -> iterator { return m_data.begin; }

    constexpr auto end() noexcept -> iterator { return m_data.end; }

    constexpr auto begin() const noexcept -> const_iterator { return m_data.begin; }

    constexpr auto end() const noexcept -> const_iterator { return m_data.end; }

    constexpr auto cbegin() const noexcept -> const_iterator { return m_data.begin; }

    constexpr auto cend() const noexcept -> const_iterator { return m_data.end; }

    constexpr auto size() const noexcept -> size_type {
        return m_data.end - m_data.begin;
    }

    constexpr auto capacity() const noexcept -> size_type {
        return m_data.storage_end - m_data.begin;
    }

    constexpr bool isEmpty() const noexcept { return m_data.begin == m_data.end; }

    constexpr void clear() noexcept {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            T* first = m_data.begin;
            for (; first != m_data.end; ++first) {
                std::ranges::destroy_at(first);
            }
        }
        m_data.end = m_data.begin;
    }

    constexpr void reserve(size_type n) {
        if(capacity() < n)
            growStorage(n);
    }

    template<std::convertible_to<T> U>
    constexpr void pushBacK(U&& value) {
        emplaceBack(std::forward<U>(value));
    }

    constexpr void popBack() { std::ranges::destroy_at(--m_data.end); }

    template<typename... Args>
    constexpr auto emplaceBack(Args&&... args) -> reference {
        if (m_data.end == m_data.storage_end) {
            growStorage(capacity() == 0 ? 1 : capacity() * 2);
        }
        std::ranges::construct_at(m_data.end, std::forward<Args>(args)...);
        ++m_data.end;
        return *(m_data.end - 1);
    }

private:
    constexpr void growStorage(std::size_t n) {
        self tmp(n);
        for (std::size_t i = 0; i < size(); ++i) {
            tmp[i] = std::move(m_data.begin[i]);
            std::ranges::destroy_at(&m_data.begin[i]);
        }
        m_data.end = m_data.begin;
        tmp.m_data.end = tmp.m_data.begin + size();
        std::ranges::swap(m_data, tmp.m_data);
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