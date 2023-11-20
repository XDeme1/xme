#pragma once

#if __cpp_concepts
#define XME_CONCEPT(Concept, T) Concept T
#define XME_REQUIRES(Requires)  requires Requires
#else
#define XME_CONCEPT(Co, T) typename T
#define XME_REQUIRES(...)
#endif
