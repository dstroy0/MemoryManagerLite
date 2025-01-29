#ifndef MEMORY_MANAGER_LITE_H
#define MEMORY_MANAGER_LITE_H
#include <Arduino.h> // For memcpy
/// @brief Class for managing memory allocation and deallocation
class MemoryManager
{
public:
    /// @brief Struct representing a memory block
    struct Block
    {
        size_t size; ///< Size of the block
        bool free;   ///< Whether the block is free
        Block *next; ///< Pointer to the next block
        Block *prev; ///< Pointer to the previous block
    };

    /// @brief Constructor for MemoryManager
    /// @param bufferSize Size of the memory buffer
    MemoryManager(size_t bufferSize);

    /// @brief Destructor for MemoryManager
    ~MemoryManager();

    /// @brief Allocate memory of a given size
    /// @param size Size of the memory to allocate
    /// @return Pointer to the allocated memory
    void *allocate(size_t size);

    /// @brief Deallocate memory
    /// @param ptr Pointer to the memory to deallocate
    void deallocate(void *ptr);

    /// @brief Reallocate memory to a new size
    /// @param ptr Pointer to the memory to reallocate
    /// @param newSize New size of the memory
    /// @return Pointer to the reallocated memory
    void *reallocate(void *ptr, size_t newSize);

    /// @brief Get the size of the memory buffer
    /// @return Size of the memory buffer
    size_t size() const;

    /// @brief Get the size of a memory block
    /// @param ptr Pointer to the memory block
    /// @return Size of the memory block
    size_t blockSize(void *ptr) const;

private:
    char *buffer;      ///< Pointer to the memory buffer
    Block *head;       ///< Pointer to the head block
    size_t bufferSize; ///< Size of the memory buffer

    /// @brief Split a memory block into two blocks
    /// @param block Pointer to the block to split
    /// @param size Size of the new block
    void splitBlock(Block *block, size_t size);

    /// @brief Merge adjacent free memory blocks
    /// @param block Pointer to the block to merge
    void mergeFreeBlocks(Block *block);
};

#endif // MEMORY_MANAGER_LITE_H