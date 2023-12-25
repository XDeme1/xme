module;
#include <xme/container/container.hpp>
export module xme.container;

export namespace xme {
using xme::allocator_c;
using xme::tuple_like_c;
using xme::pair_like_c;

using xme::AlignedData;

using xme::Array;

using xme::ArrayView;
using xme::as_bytes;
using xme::as_writable_bytes;

using xme::LinkedList;

using xme::Pair;
using xme::make_pair;

using xme::Tuple;
using xme::apply;
using xme::get;
using xme::swap;
using xme::tie;
using xme::make_tuple;
using xme::forward_as_tuple;
using xme::tuple_cat;
}
