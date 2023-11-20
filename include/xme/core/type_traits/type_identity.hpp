#pragma once

namespace xme {
template<typename T>
struct TypeIdentity {
    using type = T;
};

template<typename T>
using type_identity_t = typename TypeIdentity<T>::type;
}  // namespace xme
