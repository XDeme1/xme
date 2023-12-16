#pragma once
#include <array>
#include <bit>

#include <xme/setup.hpp>

namespace xme {
//! Provides a wrapper for an aligned storage.
//! This wrapper makes the data start in a multiple of Align
//! @param T the type of the aligned data
//! @param Align must be a power of 2 non negative number
template<typename T, std::size_t Align = alignof(T)>
class AlignedData {
public:
    static_assert(std::has_single_bit(Align), "Align must be a power of 2");
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::AlignedData must have a non-const and non-volatile T");

    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;

    //! Returns a void pointer to the address of the object
    [[nodiscard]]
    constexpr auto address() noexcept -> void* {
        return static_cast<void*>(m_data.data());
    }

    //! Returns a void pointer to the address of the object
    [[nodiscard]]
    constexpr auto address() const noexcept -> const void* {
        return static_cast<const void*>(m_data.data());
    }

    //! Returns a pointer to the object
    [[nodiscard]]
    constexpr auto data() noexcept -> pointer {
        return static_cast<T*>(address());
    }

    //! Returns a pointer to the object
    [[nodiscard]]
    constexpr auto data() const noexcept -> const_pointer {
        return static_cast<const T*>(address());
    }

private:
    alignas(Align) std::array<std::byte, sizeof(T)> m_data{};
};
}  // namespace xme
