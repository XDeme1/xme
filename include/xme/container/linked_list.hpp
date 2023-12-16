#pragma once
#include "../../../private/container/linked_list_base.hpp"
#include "concepts.hpp"
#include <iterator>
#include <memory>

namespace xme {
//! LinkedList is a singly linked list.
//! Access is O(N), unless it is the front which is O(1).
//! push and pop from front is O(1).
//! insert at the middle is O(n).
//! @param T the type of the stored element
//! @param Alloc must be an allocator that satisfies the Allocator concept
template<typename T, CAllocator Alloc = std::allocator<T>>
class LinkedList {
private:
    using node_base = detail::LinkedListNodeBase;
    using node      = detail::LinkedListNode<T>;

public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::LinkedList must have a non-const and non-volatile T");
    static_assert(std::is_same_v<T, typename Alloc::value_type>,
                  "xme::LinkedList must have the same T as its allocator");

    using allocator_type =
      typename std::allocator_traits<Alloc>::template rebind_alloc<detail::LinkedListNode<T>>;

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using iterator        = detail::LinkedListIterator<T>;
    using const_iterator  = detail::LinkedListConstIterator<T>;

    constexpr LinkedList() noexcept = default;

    //! Default constructs N nodes
    explicit constexpr LinkedList(std::size_t n) {
        node_base* curr = &m_head;
        for(; n > 0; --n) {
            curr->next = create_node();
            curr       = curr->next;
        }
    }

    //! Constructs N nodes with value
    constexpr LinkedList(std::size_t n, const T& value) {
        node_base* curr = &m_head;
        for(; n > 0; --n) {
            curr->next = create_node(value);
            curr       = curr->next;
        }
    }

    //! Constructs a LinkedList from a [first, end) range
    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr LinkedList(Iter first, Sent last) {
        range_initialize(first, last);
    }

    //! Constructs a LinkedList with the initializer_list syntax
    explicit constexpr LinkedList(std::initializer_list<T> list) {
        range_initialize(list.begin(), list.end());
    }

    //! Constructs a LinkedList by Copying elements from other.
    explicit constexpr LinkedList(const LinkedList& other) {
        range_initialize(other.begin(), other.end());
    }

    //! Constructs a LinkedList from [begin(range), end(range)) range
    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
    explicit constexpr LinkedList(R&& range) {
        range_initialize(std::ranges::begin(range), std::ranges::end(range));
    }

    //! Constructs a LinkedList by transfering elements from other
    explicit constexpr LinkedList(LinkedList&& other) noexcept {
        m_head.next       = other.m_head.next;
        other.m_head.next = nullptr;
    }

    constexpr ~LinkedList() noexcept { clear(); }

    //! Clears the current elements and copy the elements from other
    constexpr auto operator=(const LinkedList& other) -> LinkedList& {
        assign(other);
        return *this;
    }

    //! Clears the current elements and transfer elements from other
    constexpr auto operator=(LinkedList&& other) noexcept -> LinkedList& {
        clear();
        std::ranges::swap(m_head.next, other.m_head.next);
        return *this;
    }

    //! Clears the current elements and copy elements from list to the current LinkedList
    constexpr auto operator=(std::initializer_list<T> list) -> LinkedList& {
        assign(list);
        return *this;
    }

    //! Returns a iterator to the head
    constexpr auto before_begin() noexcept -> iterator { return &m_head; }
    //! Returns a iterator to the head
    constexpr auto before_begin() const noexcept -> const_iterator { return &m_head; }

    //! Returns a iterator to the first element
    constexpr auto begin() noexcept -> iterator { return m_head.next; }
    //! Returns a iterator to the first element
    constexpr auto begin() const noexcept -> const_iterator { return m_head.next; }

    //! Returns a iterator representing the end of the LinkedList
    constexpr auto end() noexcept -> iterator { return nullptr; }
    //! Returns a iterator representing the end of the LinkedList
    constexpr auto end() const noexcept -> const_iterator { return nullptr; }

    //! Returns a const iterator to the head
    constexpr auto cbefore_begin() const noexcept -> const_iterator { return &m_head; }

    //! Returns a const iterator to the first element
    constexpr auto cbegin() const noexcept -> const_iterator { return m_head.next; }
    //! Returns a const iterator representing the end of the LinkedList
    constexpr auto cend() const noexcept -> const_iterator { return nullptr; }

    //! Returns a reference to the first element
    constexpr auto front() noexcept -> reference { return *begin(); }
    //! Returns a reference to the first element
    constexpr auto front() const noexcept -> reference { return *begin(); }

    //! Returns true if there are no elements in the LinkedList
    constexpr bool is_empty() const noexcept { return m_head.next == nullptr; }

    //! Erases every element in the LinkedList
    constexpr void clear() noexcept { erase_after(before_begin(), nullptr); }

    //! Clears the current LinkedList and copy elements from a [first, end) range
    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr void assign(Iter first, Sent last) {
        auto prev = before_begin();
        auto curr = begin();
        auto _end = end();
        while(curr != _end && first != last) {
            *curr = *first;
            ++prev;
            ++curr;
            ++first;
        }

        if(first != last)
            insert_after(prev, first, last);
        else if(curr != _end)
            erase_after(prev, _end);
    }

    //! Clears the current LinkedList and copy elements from the initializer_list
    constexpr void assign(std::initializer_list<T> list) { assign(list.begin(), list.end()); }

    //! Clears the current LinkedList and copy elements from a [begin(range), end(range))
    //! range
    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
    constexpr void assign(R&& range) {
        assign(std::ranges::begin(range), std::ranges::end(range));
    }

    //! Creates a node at the front by copying value
    constexpr void push_front(const T& value) { emplace_after(&m_head, value); }
    //! Creates a node at the front by moving value
    constexpr void push_front(T&& value) { emplace_after(&m_head, std::move(value)); }

    //! Erases a node at the front
    constexpr void pop_front() noexcept { erase_after(&m_head); }

    //! Creates a node at the front by forwarding args.
    //! @returns a reference to the newly inserted element.
    template<typename... Args>
    constexpr auto emplace_front(Args&&... args) -> reference {
        return *emplace_after(&m_head, std::forward<Args>(args)...);
    }

    //! Inserts a node after pos.
    //! @returns an iterator to the new node.
    template<std::convertible_to<T> U>
    constexpr auto insert_after(const_iterator pos, U&& value) -> iterator {
        return emplace_after(pos, std::forward<U>(value));
    }

    //! Inserts a [first, last) range of nodes after pos.
    //! @returns an iterator to the last inserted element.
    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr auto insert_after(const_iterator pos, Iter first, Sent last) -> iterator {
        for(; first != last; ++first)
            pos = emplace_after(pos, *first);
        return iterator(const_cast<node_base*>(pos.current_node));
    }

    //! Inserts a [begin(range), end(range)) range of nodes after pos
    //! @returns an iterator to the last inserted element.
    template<std::ranges::input_range R>
        requires(std::is_convertible_v<std::ranges::range_reference_t<R>, T>)
    constexpr auto insert_after(const_iterator pos, R&& range) -> iterator {
        return insert_after(pos, std::ranges::begin(range), std::ranges::end(range));
    }

    //! Constructs a node after pos by forward args.
    //! @returns an iterator to the new node.
    template<typename... Args>
    constexpr auto emplace_after(const_iterator pos, Args&&... args) -> iterator {
        node_base* to       = const_cast<node_base*>(pos.current_node);
        node_base* new_node = create_node(std::forward<Args>(args)...);
        new_node->next      = to->next;
        to->next            = new_node;
        return iterator(new_node);
    }

    //! Erases the node after pos
    constexpr void erase_after(const_iterator pos) noexcept {
        node_base* tmp = const_cast<node_base*>(pos.current_node->next);
        const_cast<node_base*>(pos.current_node)->next = tmp->next;
        std::ranges::destroy_at(static_cast<node*>(tmp)->storage.data());
        m_allocator.deallocate(static_cast<node*>(tmp), 1);
    }

    //! Erases the node after pos until one before last
    constexpr void erase_after(const_iterator pos, const_iterator last) noexcept {
        node* curr{static_cast<node*>(pos.current_node->next)};

        while(curr != last.current_node) {
            node* const tmp{static_cast<node*>(curr->next)};
            std::ranges::destroy_at(curr->storage.data());
            m_allocator.deallocate(curr, 1);
            curr = tmp;
        }
        const_cast<node_base*>(pos.current_node)->next = const_cast<node_base*>(last.current_node);
    }

    //! Reverses the linked list, making the last element the first
    constexpr void reverse() noexcept {
        if(m_head.next == nullptr) return;

        node_base* tail = m_head.next;
        while(node_base* tmp = tail->next) {
            node_base* keep   = m_head.next;
            m_head.next       = tmp;
            tail->next        = tmp->next;
            m_head.next->next = keep;
        }
    }

private:
    template<typename... Args>
    constexpr auto create_node(Args&&... args) -> node* {
        node* new_node = m_allocator.allocate(1);
        try {
            std::ranges::construct_at(new_node);
            std::ranges::construct_at(new_node->storage.data(), std::forward<Args>(args)...);
        }
        catch(...) {
            m_allocator.deallocate(new_node, 1);
            throw;
        }
        return new_node;
    }

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr void range_initialize(Iter first, Sent last) {
        node_base* curr = &m_head;
        for(; first != last; ++first) {
            curr->next = create_node(*first);
            curr       = curr->next;
        }
    }

    node_base m_head;
    [[no_unique_address]]
    allocator_type m_allocator;
};
}  // namespace xme
