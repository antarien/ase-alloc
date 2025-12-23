# ase-alloc

[![Layer](https://img.shields.io/badge/Layer-0%20Foundation-blue.svg)]()
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)]()
[![Status](https://img.shields.io/badge/Status-Planned-yellow.svg)]()

> Custom memory allocators for high-performance allocation strategies

Part of [ASE - Antares Simulation Engine](../../..)

## Status

**Not Yet Implemented** - This module is a stub for future development.

## Planned Features

- **Arena Allocator**: Fast bump allocator for temporary allocations
- **Pool Allocator**: Fixed-size block allocation for frequent small objects
- **Stack Allocator**: LIFO allocation for frame-based memory
- **Linear Allocator**: Sequential allocation with bulk deallocation
- **Custom STL Allocators**: Drop-in replacements for `std::allocator`

## Motivation

ASE targets billions of entities in a persistent world. Standard allocators (`malloc`/`new`) have overhead and fragmentation issues at this scale. Custom allocators will:

- Reduce memory fragmentation
- Improve cache locality
- Minimize allocation overhead
- Enable deterministic deallocation patterns
- Support per-frame/per-system memory budgets

## Planned Usage

```cpp
// Arena allocator (not yet implemented)
#include <ase/alloc/arena.hpp>

using namespace ase::alloc;

// Frame-scoped allocations
Arena frame_arena{1024 * 1024};  // 1 MB
auto* data = frame_arena.allocate<MyStruct>();
// ... use data ...
frame_arena.reset();  // Free everything at once

// Pool allocator (not yet implemented)
#include <ase/alloc/pool.hpp>

Pool<Entity, 10000> entity_pool;  // 10k entities
Entity* e = entity_pool.allocate();
entity_pool.deallocate(e);
```

## Dependencies

### External
- C++20 standard library

### Internal
- None (Layer 0 - Foundation)

## Contributing

This module is planned but not yet implemented. If you need custom allocators:
1. Consider using existing solutions (e.g., `mimalloc`, `jemalloc`) temporarily
2. Implement allocators in this module following Layer 0 guidelines
3. Ensure no dependencies on other ASE modules

## License

Proprietary - ASE Engine

---

**Layer 0 Foundation** | No ASE dependencies | Planned
