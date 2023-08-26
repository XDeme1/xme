#pragma once
#include <cstddef>
#include <array>
#include <xme/math/type_traits.hpp>

namespace xme {
template<typename T, std::size_t Align = alignof(T)>
    requires(xme::is_power_of_2<Align>)
class AlignedData {
public:
    constexpr auto address() noexcept { return static_cast<void*>(m_data.data()); }
    constexpr auto address() const noexcept { return static_cast<const void*>(m_data.data()); }

    constexpr auto data() noexcept { return static_cast<T*>(address()); }
    constexpr auto data() const noexcept { return static_cast<const T*>(address()); }
private:
    alignas(Align) std::array<std::byte, sizeof(T)> m_data{};
};
}