#pragma once
#include <array>
#include <xme/math/type_traits.hpp>

namespace xme {
template<typename T, std::size_t Size = 1, std::size_t Align = alignof(T)>
    requires(xme::is_power_of_2<Align>)
class AlignedData {
public:
    static_assert(std::is_same_v<T, std::remove_cv_t<T>>,
                  "xme::AlignedData must have a non-const and non-volatile T");

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    constexpr auto operator[](std::size_t index) noexcept -> reference {
        return data()[index];
    }
    constexpr auto operator[](std::size_t index) const noexcept -> const_reference {
        return data()[index];
    }

    constexpr auto address() noexcept { return static_cast<void*>(m_data.data()); }
    constexpr auto address() const noexcept {
        return static_cast<const void*>(m_data.data());
    }

    constexpr auto data() noexcept { return static_cast<T*>(address()); }
    constexpr auto data() const noexcept { return static_cast<const T*>(address()); }

private:
    alignas(Align) std::array<std::byte, sizeof(T) * Size> m_data{};
};
} // namespace xme