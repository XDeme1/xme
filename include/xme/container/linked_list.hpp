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

    explicit constexpr LinkedList(std::size_t n) {
        node_base* curr = &m_head;
        for (; n > 0; --n) {
            curr->next = createNode();
            curr = curr->next;
        }
    }

    constexpr LinkedList(std::size_t n, const T& value) {
        node_base* curr = &m_head;
        for (; n > 0; --n) {
            curr->next = createNode(value);
            curr = curr->next;
        }
    }

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr LinkedList(Iter first, Sent last) {
        rangeInitialize(first, last);
    }

    explicit constexpr LinkedList(std::initializer_list<T> list) {
        rangeInitialize(list.begin(), list.end());
    }

    explicit constexpr LinkedList(const LinkedList& other) {
        rangeInitialize(other.begin(), other.end());
    }

    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
    explicit constexpr LinkedList(R&& range) {
        rangeInitialize(std::ranges::begin(range), std::ranges::end(range));
    }

    explicit constexpr LinkedList(LinkedList&& other) noexcept {
        m_head.next = other.m_head.next;
        other.m_head.next = nullptr;
    }

    constexpr ~LinkedList() noexcept { clear(); }

    constexpr auto operator=(const LinkedList& other) -> LinkedList& {
        assign(other);
        return *this;
    }

    constexpr auto operator=(LinkedList&& other) noexcept -> LinkedList& {
        clear();
        std::ranges::swap(m_head.next, other.m_head.next);
        return *this;
    }

    constexpr auto operator=(std::initializer_list<T> list) -> LinkedList& {
        assign(list);
        return *this;
    }

    constexpr auto beforeBegin() noexcept -> iterator { return &m_head; }

    constexpr auto beforeBegin() const noexcept -> const_iterator { return &m_head; }

    constexpr auto begin() noexcept -> iterator { return m_head.next; }

    constexpr auto begin() const noexcept -> const_iterator { return m_head.next; }

    constexpr auto end() noexcept -> iterator { return nullptr; }

    constexpr auto end() const noexcept -> const_iterator { return nullptr; }

    constexpr auto cbeforeBegin() const noexcept -> const_iterator { return &m_head; }

    constexpr auto cbegin() const noexcept -> const_iterator { return m_head.next; }

    constexpr auto cend() const noexcept -> const_iterator { return nullptr; }

    constexpr auto front() noexcept -> reference { return *begin(); }

    constexpr auto front() const noexcept -> reference { return *begin(); }

    constexpr bool isEmpty() const noexcept { return m_head.next == nullptr; }

    constexpr void clear() noexcept { eraseAfter(beforeBegin(), nullptr); }

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr void assign(Iter first, Sent last) {
        auto prev = beforeBegin();
        auto curr = begin();
        auto _end = end();
        while (curr != _end && first != last) {
            *curr = *first;
            ++prev;
            ++curr;
            ++first;
        }

        if (first != last)
            insertAfter(prev, first, last);
        else if (curr != _end)
            eraseAfter(prev, _end);
    }

    constexpr void assign(std::initializer_list<T> list) {
        assign(list.begin(), list.end());
    }

    template<std::ranges::input_range R>
        requires(std::convertible_to<std::ranges::range_reference_t<R>, T>)
    constexpr void assign(R&& range) {
        assign(std::ranges::begin(range), std::ranges::end(range));
    }

    constexpr void pushFront(const T& value) { emplaceAfter(&m_head, value); }

    constexpr void pushFront(T&& value) { emplaceAfter(&m_head, std::move(value)); }

    constexpr void popFront() noexcept { eraseAfter(&m_head); }

    template<typename... Args>
    constexpr auto emplaceFront(Args&&... args) -> reference {
        return *emplaceAfter(&m_head, std::forward<Args>(args)...);
    }

    template<std::convertible_to<T> U>
    constexpr auto insertAfter(const_iterator pos, U&& value) -> iterator {
        return emplaceAfter(pos, std::forward<U>(value));
    }

    template<std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    constexpr auto insertAfter(const_iterator pos, Iter first, Sent last) -> iterator {
        for (; first != last; ++first)
            pos = emplaceAfter(pos, *first);
        return iterator(const_cast<node_base*>(pos.current_node));
    }

    template<std::ranges::input_range R>
        requires(std::is_convertible_v<std::ranges::range_reference_t<R>, T>)
    constexpr auto insertAfter(const_iterator pos, R&& range) -> iterator {
        return insertAfter(pos, std::ranges::begin(range), std::ranges::end(range));
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

    constexpr void reverse() noexcept {
        if (m_head.next == nullptr)
            return;

        node_base* tail = m_head.next;
        while (node_base* tmp = tail->next) {
            node_base* keep = m_head.next;
            m_head.next = tmp;
            tail->next = tmp->next;
            m_head.next->next = keep;
        }
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

namespace std {
template<typename T>
class front_insert_iterator<xme::LinkedList<T>> {
    using self = front_insert_iterator<xme::LinkedList<T>>;

public:
    using container_type = xme::LinkedList<T>;
    using iterator_category = output_iterator_tag;

    explicit constexpr front_insert_iterator(container_type& c) noexcept
        : m_container(std::addressof(c)) {}
    constexpr auto operator=(const container_type::value_type& value) -> self& {
        m_container->pushFront(value);
        return *this;
    }

    constexpr auto operator=(container_type::value_type&& value) -> self& {
        m_container->pushFront(std::move(value));
        return *this;
    }

    // no-op
    constexpr auto operator*() noexcept -> self& { return *this; }
    // no-op
    constexpr auto operator++() noexcept -> self& { return *this; }
    // no-op
    constexpr auto operator++(int) noexcept -> self { return *this; }

protected:
    xme::LinkedList<T>* m_container;
};
} // namespace std