#pragma once
#include <cstddef>

namespace xme {
template<typename T, std::size_t Align = alignof(T)>
class AlignedData {
public:
    constexpr auto address() noexcept { return static_cast<void*>(m_data); }
    constexpr auto address() const noexcept { return static_cast<const void*>(m_data); }

    constexpr auto data() noexcept { return static_cast<T*>(address()); }
    constexpr auto data() const noexcept { return static_cast<const T*>(address()); }
private:
    alignas(Align) std::byte m_data[sizeof(T)]{};
};
}