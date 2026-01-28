#pragma once

/**
 * ASE MODULE TYPES (SSOT)
 *
 * @file        types.hpp
 * @brief       Single Source of Truth for allocation constants and types
 * @description Compile-time constants and type aliases for ase-alloc.
 *
 * @module      ase-alloc
 * @layer       0 (Foundation)
 * @created     2026-01-28
 * @modified    2026-01-28
 * @version     1.0.0
 *
 * CONTENTS:
 *   - Type Aliases (AllocHandle)
 *   - Arena Allocator Constants
 *   - Alignment Constants
 *   - Error Codes
 *
 * ECS TYPES COMPLIANCE
 *
 * [ ] All constants defined (no magic numbers in code)
 * [ ] Every constant has inline comment (English, explains purpose)
 * [ ] NO enum class (only constexpr uint8_t for enumeration values)
 * [ ] Type aliases defined
 * [ ] InvalidEntityId = UINT32_MAX defined (if needed)
 * [ ] Abbreviations documented
 * [ ] NO structs (structs belong in Components)
 *
 * ABBREVIATIONS:
 *   ALLOC = Allocation        ARN = Arena
 *   BLK = Block               SZ = Size
 *   HDL = Handle              ERR = Error
 */

#include <cstdint>

namespace ase::alloc {

/** Type Aliases */

using AllocHandle = uint32_t;  // Handle to allocated memory block

/** Arena Allocator Constants */

constexpr uint32_t ARENA_DEFAULT_SIZE = 1024 * 1024;      // Default arena size (1 MB)
constexpr uint32_t ARENA_MAX_SIZE = 64 * 1024 * 1024;     // Maximum arena size (64 MB)
constexpr uint32_t ARENA_MIN_SIZE = 4096;                 // Minimum arena size (4 KB)

/** Alignment Constants */

constexpr uint32_t ALLOC_ALIGNMENT = 8;                   // Default alignment (8 bytes for 64-bit)
constexpr uint32_t ALLOC_CACHE_LINE = 64;                 // Cache line size for alignment

/** Handle Constants */

constexpr AllocHandle ALLOC_INVALID_HANDLE = UINT32_MAX;  // Invalid allocation handle sentinel

/** Error Codes */

constexpr uint8_t ALLOC_OK = 0;                           // Allocation successful
constexpr uint8_t ALLOC_ERR_OUT_OF_MEMORY = 1;            // Arena out of memory
constexpr uint8_t ALLOC_ERR_INVALID_SIZE = 2;             // Invalid allocation size
constexpr uint8_t ALLOC_ERR_INVALID_HANDLE = 3;           // Invalid handle provided
constexpr uint8_t ALLOC_ERR_ALIGNMENT = 4;                // Alignment error

}  // namespace ase::alloc
