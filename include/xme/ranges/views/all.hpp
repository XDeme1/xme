// IWYU pragma: private, include <xme/ranges/views.hpp>
#pragma once
#include "xme/ranges/adaptors/owning_view.hpp"
#include "xme/ranges/adaptors/range_adaptor_closure.hpp"
#include "xme/ranges/adaptors/ref_view.hpp"
#include "xme/ranges/concepts.hpp"
#include <utility>

namespace xme::ranges::views {
namespace detail {
template<typename R>
concept ref_view_possible = requires { ranges::RefView{std::declval<R>()}; };

struct All : range_adaptor_closure<All> {
    template<typename R>
    constexpr auto operator()(R&& r) const noexcept {
        if constexpr(ranges::CView<std::decay_t<R>>)
            return std::forward<R>(r);
        else if constexpr(detail::ref_view_possible<R>)
            return ranges::RefView{std::forward<R>(r)};
        else
            return ranges::OwningView{std::forward<R>(r)};
    }
};
}  // namespace detail
inline constexpr detail::All all;
}  // namespace xme::ranges::views