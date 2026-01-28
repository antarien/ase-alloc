#pragma once

/**
 * ASE ALLOC - Memory Allocation Module
 *
 * @file        alloc.hpp
 * @brief       Main include file for ase-alloc module
 * @description Custom memory allocators for high-performance allocation.
 *
 * @module      ase-alloc
 * @layer       0 (Foundation)
 * @created     2026-01-28
 * @modified    2026-01-28
 * @version     1.0.0
 *
 * USAGE:
 *
 *   #include <ase/alloc/alloc.hpp>
 *
 *   // Create arena with static buffer
 *   char buffer[1024 * 1024];
 *   ase::alloc::Arena arena{buffer, sizeof(buffer)};
 *
 *   // Allocate memory
 *   char* str = static_cast<char*>(arena.allocate(100));
 *
 *   // Reset when done
 *   arena.reset();
 */

#include <ase/alloc/types.hpp>
#include <ase/alloc/arena.hpp>
