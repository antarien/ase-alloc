# ase-alloc

[![Layer](https://img.shields.io/badge/Layer-0%20Foundation-blue.svg)]()
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)]()
[![Status](https://img.shields.io/badge/Status-Active-green.svg)]()

> Custom memory allocators for high-performance allocation strategies

Part of [ASE - Antares Simulation Engine](../../..)

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
