#pragma once
#include <array>
#include <xme/bit/has_single_bit.hpp>

namespace xme {
//! Provides a wrapper for an aligned storage.
//! This wrapper makes the data start in a multiple of Align
//! If a custom align is required, is must not be lower than the default align of T
//! @param T the type of the aligned data
//! @param Align must be a power of 2 non negative number
template<typename T, std::size_t Align = alignof(T)>
    requires(xme::has_single_bit(Align))
class AlignedData {
public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::AlignedData must have a non-const and non-volatile T");
    static_assert(alignof(T) <= Align,
                  "The provided align must be higher or equal to the default align of T");

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    //! Returns a void pointer to the address of the object
    constexpr auto address() noexcept { return static_cast<void*>(m_data.data()); }

    //! Returns a void pointer to the address of the object
    constexpr auto address() const noexcept {
        return static_cast<const void*>(m_data.data());
    }

    //! Returns a pointer to the object
    constexpr auto data() noexcept { return static_cast<T*>(address()); }

    //! Returns a pointer to the object
    constexpr auto data() const noexcept { return static_cast<const T*>(address()); }

private:
    alignas(Align) std::array<std::byte, sizeof(T)> m_data{};
};
} // namespace xme