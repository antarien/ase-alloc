# ase-alloc

[![Layer](https://img.shields.io/badge/Layer-0%20Foundation-blue.svg)]()
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)]()
[![Status](https://img.shields.io/badge/Status-Active-green.svg)]()

> Custom memory allocators for high-performance allocation strategies

Part of [ASE - Antares Simulation Engine](../../..)

## Overview

The ase-alloc module provides custom memory allocators optimized for game engine workloads, replacing general-purpose heap allocation with fast, deterministic strategies. As a Layer 0 foundation library it has zero ASE dependencies and can be used by any module in the engine. Currently it offers an Arena (bump) allocator that uses a pre-allocated buffer and a simple pointer increment for O(1) allocation with zero memory overhead. The Arena is ideal for per-frame temporary allocations where many small objects are created during a single tick and then bulk-released via reset() at the end. It also serves bulk data loading scenarios such as reading JSON configuration files into a contiguous memory region managed by the ECS registry context. Future allocators may include pool allocators for fixed-size component storage, stack allocators for LIFO allocation patterns, and slab allocators for frequently created and destroyed entities. All allocators follow the principle of zero-cost abstraction — they compile to the same instructions as hand-written pointer arithmetic while providing a safe, testable API.

## Features

- **Arena Allocator**: Fast bump allocator for sequential allocations with bulk reset

## Usage

### Arena Allocator

```cpp
#include <ase/alloc/alloc.hpp>

using namespace ase::alloc;

// Create arena with pre-allocated buffer
char buffer[1024 * 1024];  // 1 MB
Arena arena{buffer, sizeof(buffer)};

// Allocate memory (O(1) bump pointer)
char* str = static_cast<char*>(arena.allocate(100));
void* data = arena.allocate_zeroed(256);  // Zero-initialized

// Check capacity
if (arena.can_allocate(1024)) {
    void* more = arena.allocate(1024);
}

// Reset all allocations at once
arena.reset();
```

### With ECS Registry Context

```cpp
// Define a buffer component for ctx()
struct ArenaBuffer {
    char data[1024 * 1024] = {};  // 1 MB buffer
};

// Register in on_start()
auto& buf = registry.ctx().emplace<ArenaBuffer>();
Arena arena{buf.data, sizeof(buf.data)};

// Use arena for allocations
char* json_str = static_cast<char*>(arena.allocate(file_size));
```

## Characteristics

| Feature | Arena |
|---------|-------|
| Allocation Time | O(1) |
| Individual Free | No |
| Bulk Free | Yes (reset) |
| Memory Overhead | Zero |
| Cache Friendly | Yes |

## Dependencies

### External
- C++20 standard library (`<cstdint>`)

### Internal
- None (Layer 0 - Foundation)

## License

Proprietary - ASE Engine

---

**Layer 0 Foundation** | No ASE dependencies | Header-only
