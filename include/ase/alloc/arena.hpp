#pragma once

/**
 * ASE ALLOC - Arena Allocator
 *
 * @file        arena.hpp
 * @brief       Fast bump allocator for sequential allocations
 * @description Arena allocator that uses a pre-allocated buffer. All allocations
 *              are sequential (bump pointer). Memory is freed all at once via reset().
 *
 * @module      ase-alloc
 * @layer       0 (Foundation)
 * @created     2026-01-28
 * @modified    2026-01-28
 * @version     1.0.0
 *
 * USAGE:
 *
 *   // Option 1: Static buffer
 *   char buffer[1024 * 1024];
 *   ase::alloc::Arena arena{buffer, sizeof(buffer)};
 *
 *   // Option 2: Registry ctx() buffer
 *   auto& buffer = registry.ctx().emplace<ArenaBuffer>();
 *   ase::alloc::Arena arena{buffer.data, sizeof(buffer.data)};
 *
 *   // Allocate memory (returns void*, caller casts)
 *   char* str = static_cast<char*>(arena.allocate(100));
 *
 *   // Reset all allocations
 *   arena.reset();
 *
 * CHARACTERISTICS:
 *   - O(1) allocation (bump pointer)
 *   - No individual deallocation (reset frees all)
 *   - Cache-friendly sequential layout
 *   - Zero overhead per allocation
 */

#include <ase/alloc/types.hpp>
#include <cstdint>

namespace ase::alloc {

/**
 * @brief Arena allocator using external buffer
 *
 * The arena does not own the buffer - caller is responsible for
 * providing and managing the underlying memory.
 */
class Arena {
public:
    /**
     * @brief Construct arena with external buffer
     * @param buffer Pointer to pre-allocated memory
     * @param size Size of buffer in bytes
     */
    Arena(void* buffer, uint32_t size)
        : buffer_(static_cast<char*>(buffer))
        , size_(size)
        , offset_(0) {}

    /**
     * @brief Allocate raw bytes from arena
     * @param num_bytes Number of bytes to allocate
     * @param alignment Alignment requirement (default: 8)
     * @return Pointer to allocated memory, or nullptr if out of space
     *
     * Caller is responsible for casting to appropriate type.
     */
    void* allocate(uint32_t num_bytes, uint32_t alignment = ALLOC_ALIGNMENT) {
        // Align the current offset
        uint32_t aligned_offset = align_up(offset_, alignment);

        // Check if allocation fits
        if (aligned_offset + num_bytes > size_) {
            return nullptr;  // Out of memory
        }

        // Bump the pointer
        void* result = buffer_ + aligned_offset;
        offset_ = aligned_offset + num_bytes;

        return result;
    }

    /**
     * @brief Allocate and zero-initialize bytes
     * @param num_bytes Number of bytes to allocate
     * @param alignment Alignment requirement
     * @return Pointer to zero-initialized memory, or nullptr if out of space
     */
    void* allocate_zeroed(uint32_t num_bytes, uint32_t alignment = ALLOC_ALIGNMENT) {
        void* raw_ptr = allocate(num_bytes, alignment);
        if (raw_ptr != nullptr) {
            // Zero-initialize via char pointer
            char* byte_ptr = static_cast<char*>(raw_ptr);
            for (uint32_t i = 0; i < num_bytes; ++i) {
                byte_ptr[i] = 0;
            }
        }
        return raw_ptr;
    }

    /**
     * @brief Reset arena (free all allocations)
     *
     * This does not zero the memory, just resets the offset.
     */
    void reset() {
        offset_ = 0;
    }

    /**
     * @brief Get remaining capacity in bytes
     */
    uint32_t remaining() const {
        return size_ - offset_;
    }

    /**
     * @brief Get current allocation offset
     */
    uint32_t used() const {
        return offset_;
    }

    /**
     * @brief Get total capacity in bytes
     */
    uint32_t capacity() const {
        return size_;
    }

    /**
     * @brief Check if arena has space for allocation
     * @param num_bytes Number of bytes needed
     */
    bool can_allocate(uint32_t num_bytes) const {
        return align_up(offset_, ALLOC_ALIGNMENT) + num_bytes <= size_;
    }

private:
    /**
     * @brief Align value up to given alignment
     */
    static uint32_t align_up(uint32_t value, uint32_t alignment) {
        return (value + alignment - 1) & ~(alignment - 1);
    }

    char* buffer_;     // External buffer (not owned)
    uint32_t size_;    // Total buffer size
    uint32_t offset_;  // Current allocation offset
};

}  // namespace ase::alloc
