#pragma once

/**
 * ASE CORE INFRASTRUCTURE HEADER
 *
 * @file        alloc.hpp
 * @brief       ase::alloc - the module entry point and the place its size contract is asserted
 * @description The one include a consumer needs for arena allocation. It pulls in the module's
 *              two halves - types.hpp with the aliases, size bounds, alignment and error codes,
 *              arena.hpp with the bump allocator itself - so that no caller has to know the
 *              module's internal file split.
 *
 *              IT ALSO CARRIES THE CONTRACT BETWEEN THOSE TWO HALVES, and that is why this file
 *              has a namespace of its own rather than being a bare list of includes. The size
 *              bounds and the alignment constants are declared in types.hpp and CONSUMED by
 *              arena.hpp; nothing in either file checks that they are mutually consistent. This
 *              header is the only place that sees both, so the static_asserts below live here.
 *              They cost nothing at runtime and they fail the compile - not a test run - the day
 *              somebody edits a bound into an order that the allocator cannot honour.
 *
 *              Import via:
 *                #include <ase/alloc/alloc.hpp>
 *
 *                char buffer[ase::alloc::ARENA_DEFAULT_SIZE];
 *                ase::alloc::Arena arena{buffer, sizeof(buffer)};
 *                char* str = static_cast<char*>(arena.allocate(100));
 *                arena.reset();
 *
 * @module      ase-alloc
 * @layer       0 (Foundation)
 * @category    structure/memory/allocation
 * @created     2026-01-28
 * @modified    2026-08-20
 * @version     1.1.0
 *
 * CORE INFRASTRUCTURE COMPLIANCE
 *
 * [ ] NOT an ECS Component or System
 * [ ] Layer dependencies correct (L0: no ASE deps, L1: L0 only)
 * [ ] No global mutable state (constexpr/const only)
 * [ ] No singletons or static mutable variables
 * [ ] Thread-safe by design (pure functions or explicit mutex)
 * [ ] All public functions documented with @brief, @param, @return
 * [ ] constexpr where possible (compile-time evaluation)
 * [ ] noexcept where possible (no-throw guarantee)
 * [ ] [[nodiscard]] on functions returning values
 * [ ] No magic numbers (use named constants)
 * [ ] No implicit conversions (use explicit constructors)
 * [ ] Header-only OR header+cpp pattern (not mixed)
 * [ ] Include guards via #pragma once
 * [ ] Namespace matches module: ase::{module}
 * [ ] No circular dependencies
 * [ ] No macros (except include guards) - use constexpr/templates
 * [ ] API stable (changes require version bump)
 */

#include <ase/alloc/types.hpp>
#include <ase/alloc/arena.hpp>

namespace ase::alloc {

/**
 * The module's size contract, stated once where both halves are visible.
 *
 * An arena is handed a caller-owned buffer and bump-allocates inside it. The three bounds in
 * types.hpp only mean something in this order; a default below the minimum or above the maximum
 * would be a buffer size the allocator is documented to reject.
 */
static_assert(ARENA_MIN_SIZE <= ARENA_DEFAULT_SIZE,
              "ARENA_DEFAULT_SIZE must not fall below ARENA_MIN_SIZE");
static_assert(ARENA_DEFAULT_SIZE <= ARENA_MAX_SIZE,
              "ARENA_DEFAULT_SIZE must not exceed ARENA_MAX_SIZE");

/**
 * The alignment contract. Every bump step rounds up to ALLOC_ALIGNMENT, so a cache line that is
 * not a whole number of alignment steps would make cache-line placement unreachable by
 * construction - the allocator could never land an allocation on one.
 */
static_assert(ALLOC_ALIGNMENT > 0u, "ALLOC_ALIGNMENT must be positive");
static_assert(ALLOC_CACHE_LINE % ALLOC_ALIGNMENT == 0u,
              "ALLOC_CACHE_LINE must be a whole number of ALLOC_ALIGNMENT steps");

/**
 * The handle sentinel must be outside the range of any handle the module can hand out, which is
 * what makes ALLOC_INVALID_HANDLE distinguishable from a real allocation.
 */
static_assert(ALLOC_INVALID_HANDLE == static_cast<AllocHandle>(-1),
              "ALLOC_INVALID_HANDLE must be the maximum value of AllocHandle");

}  // namespace ase::alloc
