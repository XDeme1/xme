#pragma once
#include <cstddef>

namespace xme {
template<typename T, std::size_t Align = alignof(T)>
class AlignedData {
public:
    constexpr auto& address() noexcept { return static_cast<void*>(m_Data); }
    constexpr auto& address() const noexcept { return static_cast<void*>(m_Data); }

    constexpr auto& data() noexcept { return static_cast<T*>(address()); }
    constexpr auto& data() const noexcept { return static_cast<T*>(address()); }
private:
    alignas(Align) std::byte m_Data[sizeof(T)];
};
}