#pragma once
#include <utility>
#include <iterator>

namespace xme::detail {
    template<typename T>
    struct Contiguousiterator 
    {
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        
        using iterator_concept = std::iterator_traits<T*>::iterator_concept;
        using iterator_category = std::iterator_traits<T*>::iterator_concept;

        constexpr Contiguousiterator() = default;
        constexpr Contiguousiterator(const Contiguousiterator&) = default;
        constexpr Contiguousiterator(Contiguousiterator&&) = default;
        constexpr auto operator=(const Contiguousiterator&) -> Contiguousiterator& = default;
        constexpr auto operator=(Contiguousiterator&&) -> Contiguousiterator& = default;
        
        constexpr Contiguousiterator(pointer p) noexcept
            : Current(p) {}

        template<typename U>
        constexpr Contiguousiterator(const Contiguousiterator<U>& rhs)
            : Current(rhs.data()) {}

        constexpr auto data() const noexcept -> pointer { return Current; }

        constexpr auto operator*() const noexcept -> reference
        { return *Current; }

        constexpr auto operator->() const noexcept -> pointer
        { return Current; }

        constexpr auto operator+(difference_type n) const noexcept -> Contiguousiterator
        { return Contiguousiterator(Current + n); }
        constexpr auto operator-(difference_type n) const noexcept -> Contiguousiterator
        { return Contiguousiterator(Current - n); }

        constexpr auto operator+(const Contiguousiterator<T>& rhs) const noexcept -> difference_type
        { return Current + rhs.Current; }
        constexpr auto operator-(const Contiguousiterator<T>& rhs) const noexcept -> difference_type
        { return Current - rhs.Current; }

        constexpr auto operator++() noexcept -> Contiguousiterator&
        { 
            ++Current;
            return *this;
        }
        constexpr auto operator--() noexcept -> Contiguousiterator&
        {
            --Current;
            return *this;
        }

        constexpr auto operator++(int) noexcept -> Contiguousiterator
        { 
            Contiguousiterator copy{Current};
            ++Current;
            return copy;
        }
        constexpr auto operator--(int) noexcept -> Contiguousiterator
        {
            Contiguousiterator copy{Current};
            --Current;
            return copy;
        }

        constexpr auto operator[](size_type index) const noexcept -> reference
        { return Current[index]; }

        constexpr auto operator+=(difference_type n) noexcept -> Contiguousiterator&
        {
            Current += n;
            return *this;
        }
        constexpr auto operator-=(difference_type n) noexcept -> Contiguousiterator&
        {
            Current -= n;
            return *this;
        }

        constexpr auto operator<=>(const Contiguousiterator& it) const noexcept = default;
    private:
        pointer Current = nullptr;
    };

    template<typename T>
    constexpr auto operator+(typename Contiguousiterator<T>::difference_type n, const Contiguousiterator<T>& rhs) noexcept -> Contiguousiterator<T>
    { return Contiguousiterator(rhs.data() + n); }
}