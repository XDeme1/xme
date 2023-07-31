#pragma once
#include <array>

#include "../../../private/math/forward.hpp"
#include "matrices/matrix2x2.hpp"

namespace xme {
template <typename T, std::size_t Cols, std::size_t Rows>
class Matrix {
  public:
    using column_type = Vector<T, Cols>;

  private:
    std::array<column_type, Cols> a;
};
} // namespace xme