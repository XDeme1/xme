#pragma once
#include <xme/container/aligned_data.hpp>

namespace xme::detail {
struct LinkedListNodeBase {
    LinkedListNodeBase* next = nullptr;
};

template<typename T>
struct LinkedListNode : LinkedListNodeBase {
    xme::AlignedData<T> storage;
};

template<typename T>
struct LinkedListIterator {
private:
    using node_base = detail::LinkedListNodeBase;
    using node = detail::LinkedListNode<T>;
    using self = LinkedListIterator<T>;

public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;

    constexpr LinkedListIterator() noexcept = default;

    constexpr LinkedListIterator(node_base* ptr) noexcept : current_node(ptr) {}
    
    constexpr auto operator->() const noexcept -> pointer {
        return static_cast<node*>(current_node)->storage.data();
    }

    constexpr auto operator*() const noexcept -> reference {
        return *static_cast<node*>(current_node)->storage.data();
    }

    constexpr auto operator++() noexcept -> self& {
        current_node = current_node->next;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> self {
        self tmp{*this};
        current_node = current_node->next;
        return tmp;
    }

    constexpr auto operator<=>(const LinkedListIterator&) const noexcept = default;

    constexpr bool operator==(const LinkedListIterator&) const noexcept = default;

    node_base* current_node = nullptr;
};

template<typename T>
struct LinkedListConstIterator {
private:
    using node_base = detail::LinkedListNodeBase;
    using node = detail::LinkedListNode<T>;
    using self = LinkedListConstIterator<T>;
    using iterator = LinkedListIterator<T>;
public:

    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    constexpr LinkedListConstIterator() noexcept = default;

    constexpr LinkedListConstIterator(const node_base* ptr) noexcept : current_node(ptr) {}

    constexpr LinkedListConstIterator(const iterator& it) noexcept
        : current_node(it.current_node) {}
    
    constexpr auto operator->() const noexcept -> pointer {
        return static_cast<const node*>(current_node)->storage.data();
    }

    constexpr auto operator*() const noexcept -> reference {
        return *static_cast<const node*>(current_node)->storage.data();
    }

    constexpr auto operator++() noexcept -> LinkedListConstIterator& {
        current_node = current_node->next;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> LinkedListConstIterator {
        self tmp{*this};
        current_node = current_node->next;
        return tmp;
    }

    constexpr auto operator<=>(const LinkedListConstIterator&) const noexcept = default;

    constexpr bool operator==(const LinkedListConstIterator&) const noexcept = default;

    const node_base* current_node = nullptr;
};
} // namespace xme::detail