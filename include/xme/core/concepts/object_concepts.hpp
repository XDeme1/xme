#pragma once
#include <xme/core/concepts/constructible.hpp>
#include <xme/core/concepts/assignable.hpp>
#include <xme/core/concepts/swappable.hpp>
#include <xme/core/concepts/equality_comparable.hpp>

namespace xme {
template<typename T>
concept CMovable =
  std::is_object_v<T> && CMoveConstructible<T> && CAssignableFrom<T&, T> && CSwappable<T>;

template<typename T>
concept CCopyable = CCopyConstructible<T> && CMovable<T> && CAssignableFrom<T&, T&>
                    && CAssignableFrom<T&, const T&> && CAssignableFrom<T&, const T>;

template<typename T>
concept CSemiregular = CCopyable<T> && CDefaultInitializable<T>;

template<typename T>
concept CRegular = CSemiregular<T> && CEqualityComparable<T>;
}  // namespace xme
