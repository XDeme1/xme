#pragma once
#include "array.hpp"
#include "xme/container/icontainer.hpp"

namespace xme {
//! Heap is a priority queue stored in a contiguous array.
//! It is weakly sorted.
//! std::less<> == MaxHeap and std::greater<> == MinHeap
//! Pushing and poping is O(log(N))
//! @param T the type of the stored element
//! @param Alloc must be an allocator that satisfies the Allocator concept
template<typename T, std::ranges::contiguous_range Container = Array<T>, typename Cmp = std::less<>>
class Heap : public IContainer<Heap<T, Container, Cmp>> {
public:
    using container_type  = Container;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;
    using const_iterator  = typename Container::const_iterator;

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
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
                && (!std::is_same_v<Heap, std::remove_cvref_t<R>>)
    constexpr Heap(R&& range) {
        m_array.reserve(std::ranges::size(range));
        auto first = std::ranges::begin(range);
        auto last  = std::ranges::end(range);
        for(; first != last; ++first) {
            push(*first);
        }
    }

    [[nodiscard]]
    constexpr auto begin() const noexcept -> const_iterator {
        return m_array.cbegin();
    }

    [[nodiscard]]
    constexpr auto end() const noexcept -> const_iterator {
        return m_array.cend();
    }

    //! Pop the front element and rearrange elements to keep a week sort.
    //! O(log(N)) operation
    constexpr void pop() noexcept {
        assert(m_array.size() > 0);
        std::ranges::swap(m_array.front(), m_array.back());
        m_array.pop_back();
        heapfy_down(0);
    }

    //! Push value to the end of the queue and pushes
    //! to the front until needed to keep a week sort.
    //! O(log(N)) operation
    template<std::convertible_to<T> U>
    constexpr void push(U&& value) {
        m_array.push_back(std::forward<U>(value));
        heapfy_up(m_array.size() - 1);
    }

    //! Push value to the end of the queue and pushes
    //! to the front until needed to keep a week sort.
    //! O(log(N)) operation
    template<typename... Args>
    constexpr void emplace(Args&&... args) {
        m_array.emplace_back(std::forward<Args>(args)...);
        heapfy_up(m_array.size() - 1);
    }

private:
    [[nodiscard]]
    constexpr auto parent(difference_type index) const noexcept -> std::ptrdiff_t {
        return (index - 1) / 2;
    }

    [[nodiscard]]
    constexpr auto left_child(size_type index) const noexcept -> size_type {
        return index * 2 + 1;
    }

    [[nodiscard]]
    constexpr auto right_child(size_type index) const noexcept -> size_type {
        return index * 2 + 2;
    }

    constexpr void heapfy_up(size_type index) noexcept {
        for(auto parent_heap = parent(index); index != 0;) {
            if(!m_compare(m_array[parent_heap], m_array[index]))
                return;

            std::ranges::swap(m_array[parent_heap], m_array[index]);
            index       = parent_heap;
            parent_heap = parent(parent_heap);
        }
    }

    constexpr void heapfy_down(size_type index) noexcept {
        const auto lidx = left_child(index);
        const auto ridx = right_child(index);

        std::size_t swap_index = index;
        if(lidx < m_array.size() && m_compare(m_array[swap_index], m_array[lidx]))
            swap_index = lidx;
        if(ridx < m_array.size() && m_compare(m_array[swap_index], m_array[ridx]))
            swap_index = ridx;
        if(swap_index != index) {
            std::ranges::swap(m_array[index], m_array[swap_index]);
            heapfy_down(swap_index);
        }
    }

    container_type m_array;
    [[no_unique_address]]
    Cmp m_compare;
};
}  // namespace xme
