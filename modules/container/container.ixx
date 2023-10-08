module;
#include <xme/container/container.hpp>
export module xme.container;

export namespace xme {
using xme::CAllocator;
using xme::CTupleLike;
using xme::CPairLike;

using xme::AlignedData;

using xme::Array;

using xme::ArrayView;
using xme::asBytes;
using xme::asWritableBytes;

using xme::LinkedList;

using xme::Pair;
using xme::makePair;

using xme::Tuple;
using xme::apply;
using xme::get;
using xme::swap;
using xme::tie;
using xme::makeTuple;
using xme::forwardAsTuple;
using xme::tupleCat;
}