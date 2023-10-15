#pragma once
#include "array.hpp"

namespace xme {
//! Heap is a priority queue stored in a contiguous array.
//! It is weakly sorted.
//! std::less<> == MaxHeap and std::greater<> == MinHeap
//! Pushing and poping is O(log(N))
//! @param T the type of the stored element
//! @param Alloc must be an allocator that satisfies the Allocator concept
template<typename T, typename Cmp = std::less<>>
class Heap {
public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using const_iterator = ContiguousIterator<const T>;

    constexpr Heap() = default;

    //! Creates a heap with [first, last) elements.
    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr Heap(Iter first, Sent last) {
        if constexpr(std::contiguous_iterator<Iter>)
            m_array.reserve(std::ranges::distance(first, last));
        for(; first != last; ++first) {
            push(*first);
        }
    }

    //! Creates a heap with [begin(range), end(range)) elements.
    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>) &&
        (!std::is_same_v<Heap, std::remove_cvref_t<R>>)
    constexpr Heap(R&& range) {
        m_array.reserve(std::ranges::size(range));
        auto first = std::ranges::begin(range);
        auto last = std::ranges::end(range);
        for(; first != last; ++first) {
            push(*first);
        }
    }

    constexpr bool isEmpty() const noexcept { return m_array.isEmpty(); }

    constexpr auto size() const noexcept -> size_type { return m_array.size(); }

    constexpr auto begin() const noexcept -> const_iterator { return m_array.cbegin(); }

    constexpr auto end() const noexcept -> const_iterator { return m_array.cend(); }

    constexpr auto front() const noexcept -> const_reference { return *begin(); }

    //! Pop the front element and rearrange elements to keep a week sort.
    //! O(log(N)) operation
    constexpr void pop() noexcept {
        assert(m_array.size() > 0);
        std::ranges::swap(m_array.front(), m_array.back());
        m_array.popBack();
        heapfyDown(0);
    }

    //! Push value to the end of the queue and pushes
    //! to the front until needed to keep a week sort.
    //! O(log(N)) operation
    template<std::convertible_to<T> U>
    constexpr void push(U&& value) {
        m_array.pushBack(std::forward<U>(value));
        heapfyUp(m_array.size() - 1);
    }

    //! Push value to the end of the queue and pushes
    //! to the front until needed to keep a week sort.
    //! O(log(N)) operation
    template<typename... Args>
    constexpr void emplace(Args&&... args) {
        m_array.emplaceBack(std::forward<Args>(args)...);
        heapfyUp(m_array.size() - 1);
    }

private:
    constexpr auto parent(difference_type index) const noexcept -> std::ptrdiff_t {
        return (index - 1) / 2;
    }

    constexpr auto leftChild(size_type index) const noexcept -> size_type {
        return index * 2 + 1;
    }

    constexpr auto rightChild(size_type index) const noexcept -> size_type {
        return index * 2 + 2;
    }

    constexpr void heapfyUp(size_type index) noexcept {
        for (auto parent_heap = parent(index); index != 0;) {
            if (!m_compare(m_array[parent_heap], m_array[index]))
                return;

            std::ranges::swap(m_array[parent_heap], m_array[index]);
            index = parent_heap;
            parent_heap = parent(parent_heap);
        }
    }

    constexpr void heapfyDown(size_type index) noexcept {
        const auto lidx = leftChild(index);
        const auto ridx = rightChild(index);

        std::size_t swap_index = index;
        if (lidx < m_array.size() && m_compare(m_array[swap_index], m_array[lidx]))
            swap_index = lidx;
        if (ridx < m_array.size() && m_compare(m_array[swap_index], m_array[ridx]))
            swap_index = ridx;
        if (swap_index != index) {
            std::ranges::swap(m_array[index], m_array[swap_index]);
            heapfyDown(swap_index);
        }
    }

    xme::Array<T> m_array;
    [[no_unique_address]] Cmp m_compare;
};
} // namespace xme