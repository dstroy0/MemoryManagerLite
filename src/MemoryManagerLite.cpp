#include "MemoryManagerLite.h"

/// @brief Constructor for MemoryManager
/// @param bufferSize Size of the memory buffer
MemoryManager::MemoryManager(size_t bufferSize) : bufferSize(bufferSize)
{
    buffer = new char[bufferSize];
    head = reinterpret_cast<Block *>(buffer);
    head->size = bufferSize - sizeof(Block);
    head->free = true;
    head->next = head;
    head->prev = head;
}

/// @brief Destructor for MemoryManager
MemoryManager::~MemoryManager()
{
    delete[] buffer;
}

/// @brief Allocate memory of a given size
/// @param size Size of the memory to allocate
/// @return Pointer to the allocated memory
void *MemoryManager::allocate(size_t size)
{
    // Ensure size is aligned to 4 bytes
    size = (size + 3) & ~3;
    
    Block *current = head;
    do
    {
        if (current->free && current->size >= size)
        {
            if (current->size > size + sizeof(Block))
            {
                splitBlock(current, size);
            }
            current->free = false;
            return reinterpret_cast<void *>(reinterpret_cast<char *>(current) + sizeof(Block));
        }
        current = current->next;
    } while (current != head);
    return nullptr; // No suitable block found
}

/// @brief Deallocate memory
/// @param ptr Pointer to the memory to deallocate
void MemoryManager::deallocate(void *ptr)
{
    if (!ptr)
        return; // error
    Block *block = reinterpret_cast<Block *>(reinterpret_cast<char *>(ptr) - sizeof(Block));
    block->free = true;
    mergeFreeBlocks(block);
}

/// @brief Reallocate memory to a new size
/// @param ptr Pointer to the memory to reallocate
/// @param newSize New size of the memory
/// @return Pointer to the reallocated memory
void *MemoryManager::reallocate(void *ptr, size_t newSize)
{
    if (!ptr)
        return allocate(newSize);
    Block *block = reinterpret_cast<Block *>(reinterpret_cast<char *>(ptr) - sizeof(Block));
    if (block->size >= newSize)
    {
        if (block->size > newSize + sizeof(Block))
        {
            splitBlock(block, newSize);
        }
        return ptr;
    }
    else
    {
        void *newPtr = allocate(newSize);
        if (newPtr)
        {
            memcpy(newPtr, ptr, block->size);
            deallocate(ptr);
        }
        return newPtr;
    }
}

/// @brief Get the size of the memory buffer
/// @return Size of the memory buffer
size_t MemoryManager::size() const
{
    return bufferSize;
}

/// @brief Get the size of a memory block
/// @param ptr Pointer to the memory block
/// @return Size of the memory block
size_t MemoryManager::blockSize(void *ptr) const
{
    if (!ptr)
        return 0;
    Block *block = reinterpret_cast<Block *>(reinterpret_cast<char *>(ptr) - sizeof(Block));
    return block->size;
}

/// @brief Split a memory block into two blocks
/// @param block Pointer to the block to split
/// @param size Size of the new block
void MemoryManager::splitBlock(Block *block, size_t size)
{
    Block *newBlock = reinterpret_cast<Block *>(reinterpret_cast<char *>(block) + sizeof(Block) + size);
    newBlock->size = block->size - size - sizeof(Block);
    newBlock->free = true;
    newBlock->next = block->next;
    newBlock->prev = block;
    block->next->prev = newBlock;
    block->next = newBlock;
    block->size = size;
}

/// @brief Merge adjacent free memory blocks
/// @param block Pointer to the block to merge
void MemoryManager::mergeFreeBlocks(Block *block)
{
    if (block->next->free)
    {
        block->size += sizeof(Block) + block->next->size;
        block->next = block->next->next;
        block->next->prev = block;
    }
    if (block->prev->free)
    {
        block->prev->size += sizeof(Block) + block->size;
        block->prev->next = block->next;
        block->next->prev = block->prev;
    }
}