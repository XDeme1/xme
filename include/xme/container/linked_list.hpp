#pragma once
#include "aligned_data.hpp"
#include <memory>
#include <ranges>
#include <type_traits>

#include "../../../private/container/linked_list_base.hpp"

namespace xme {
template<typename T, typename Alloc = std::allocator<T>>
class LinkedList
    : std::allocator_traits<Alloc>::template rebind_alloc<detail::LinkedListNode<T>> {
private:
    using node_base = detail::LinkedListNodeBase;
    using node = detail::LinkedListNode<T>;

public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::LinkedList must have a non-const and non-volatile T");
    static_assert(std::is_same_v<T, typename Alloc::value_type>,
                  "xme::LinkedList must have the same T as its allocator");

    using allocator =
        std::allocator_traits<Alloc>::template rebind_alloc<detail::LinkedListNode<T>>;

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using iterator = detail::LinkedListIterator<T>;
    using const_iterator = detail::LinkedListConstIterator<T>;

    constexpr LinkedList() noexcept = default;

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr LinkedList(Iter first, Sent last) {
        rangeInitialize(first, last);
    }

    constexpr LinkedList(std::initializer_list<T> list) {
        rangeInitialize(list.begin(), list.end());
    }

    template<std::ranges::range R>
    constexpr LinkedList(R&& range) {
        rangeInitialize(std::ranges::begin(range), std::ranges::end(range));
    }

    constexpr LinkedList(LinkedList&& other) noexcept {
        m_head.next = other.m_head.next;
        other.m_head.next = nullptr;
    }

    constexpr ~LinkedList() noexcept { clear(); }

    constexpr auto beforeBegin() noexcept -> iterator { return iterator(&m_head); }

    constexpr auto beforeBegin() const noexcept -> const_iterator {
        return const_iterator(&m_head);
    }

    constexpr auto begin() noexcept -> iterator { return iterator(m_head.next); }

    constexpr auto begin() const noexcept -> const_iterator {
        return const_iterator(m_head.next);
    }

    constexpr auto end() noexcept -> iterator { return iterator(nullptr); }

    constexpr auto end() const noexcept -> const_iterator {
        return const_iterator(nullptr);
    }

    constexpr auto cbeforeBegin() const noexcept -> const_iterator {
        return const_iterator(&m_head);
    }

    constexpr auto cbegin() const noexcept -> const_iterator {
        return const_iterator(m_head.next);
    }

    constexpr auto cend() const noexcept -> const_iterator {
        return const_iterator(nullptr);
    }

    constexpr auto front() noexcept -> reference { return *begin(); }

    constexpr auto front() const noexcept -> reference { return *begin(); }

    constexpr bool isEmpty() const noexcept { return m_head.next == nullptr; }

    constexpr void clear() noexcept { eraseAfter(beforeBegin(), nullptr); }

    constexpr void pushFront(const T& value) { emplaceAfter(&m_head, value); }

    constexpr void pushFront(T&& value) { emplaceAfter(&m_head, std::move(value)); }

    constexpr void popFront() noexcept { eraseAfter(&m_head); }

    template<typename... Args>
    constexpr auto emplaceFront(Args&&... args) -> reference {
        return *emplaceAfter(&m_head, std::forward<Args>(args)...);
    }

    constexpr auto insertAfter(const_iterator pos, const T& value) noexcept -> iterator {
        return emplaceAfter(pos, value);
    }

    constexpr auto insertAfter(const_iterator pos, T&& value) noexcept -> iterator {
        return emplaceAfter(pos, std::move(value));
    }

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr auto insertAfter(const_iterator pos, Iter first, Sent last) -> iterator {
        for (; first != last; ++first)
            pos = emplaceAfter(pos, *first);
        return iterator(const_cast<node_base*>(pos.current_node));
    }

    template<std::ranges::range R>
    constexpr auto insertAfter(const_iterator pos, R&& range) -> iterator {
        auto first = std::ranges::begin(range);
        auto end = std::ranges::end(range);
        for (; first != end; ++first)
            pos = emplaceAfter(pos, *first);
        return iterator(const_cast<node_base*>(pos.current_node));
    }

    template<typename... Args>
    constexpr auto emplaceAfter(const_iterator pos, Args&&... args) -> iterator {
        node_base* to = const_cast<node_base*>(pos.current_node);
        node_base* new_node = createNode(std::forward<Args>(args)...);
        new_node->next = to->next;
        to->next = new_node;
        return iterator(new_node);
    }

    constexpr void eraseAfter(const_iterator pos) noexcept {
        node_base* tmp = const_cast<node_base*>(pos.current_node->next);
        const_cast<node_base*>(pos.current_node)->next = tmp->next;
        std::ranges::destroy_at(static_cast<node*>(tmp)->storage.data());
        deallocate(static_cast<node*>(tmp));
    }

    constexpr void eraseAfter(const_iterator pos, const_iterator last) noexcept {
        node* curr{static_cast<node*>(pos.current_node->next)};

        while (curr != last.current_node) {
            node* const tmp{static_cast<node*>(curr->next)};
            std::ranges::destroy_at(curr->storage.data());
            deallocate(curr);
            curr = tmp;
        }
        const_cast<node_base*>(pos.current_node)->next =
            const_cast<node_base*>(last.current_node);
    }

private:
    constexpr auto allocate() noexcept -> node* {
        return static_cast<allocator*>(this)->allocate(1);
    }

    constexpr auto deallocate(node* ptr) noexcept {
        static_cast<allocator*>(this)->deallocate(ptr, 1);
    }

    template<typename... Args>
    constexpr auto createNode(Args&&... args) -> node* {
        node* new_node = allocate();
        try {
            std::ranges::construct_at(new_node);
            std::ranges::construct_at(new_node->storage.data(),
                                      std::forward<Args>(args)...);
        } catch (...) {
            deallocate(new_node);
            throw;
        }
        return new_node;
    }

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr void rangeInitialize(Iter first, Sent last) {
        node_base* curr = &m_head;
        for (; first != last; ++first) {
            curr->next = createNode(*first);
            curr = curr->next;
        }
    }

    node_base m_head;
};
} // namespace xme