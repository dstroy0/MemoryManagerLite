# MemoryManagerLite Library

## Overview
The MemoryManagerLite library provides a simple and efficient way to manage dynamic memory allocation and deallocation in Arduino projects. It allows users to allocate, deallocate, and reallocate memory blocks, while also keeping track of memory usage.

## Features
- Custom memory management with a block structure.
- Efficient allocation and deallocation of memory.
- Ability to reallocate memory blocks.
- Functions to retrieve the size of the memory buffer and individual blocks.

## Installation
To install the MemoryManagerLite library, follow these steps:
1. Download the library files.
2. Place the `MemoryManagerLite` folder in your Arduino libraries directory (usually found in `Documents/Arduino/libraries`).
3. Restart the Arduino IDE.

## Usage
To use the MemoryManagerLite library in your Arduino sketch, include the header file:

```cpp
#include <MemoryManagerLite.h>
```

### Example
Here is a simple example demonstrating how to use the MemoryManager class:

```cpp
#include <MemoryManagerLite.h>

MemoryManager memoryManager(1024); // Create a memory manager with 1024 bytes

void setup() {
    Serial.begin(9600);

    // Allocate memory
    void* ptr = memoryManager.allocate(100);
    if (ptr) {
        Serial.println("Memory allocated successfully.");
    }

    // Get the size of the allocated block
    size_t blockSize = memoryManager.blockSize(ptr);
    Serial.print("Block size: ");
    Serial.println(blockSize);

    // Deallocate memory
    memoryManager.deallocate(ptr);
    Serial.println("Memory deallocated.");
}

void loop() {
    // Your code here
}
```

## API Reference
- `MemoryManager(size_t bufferSize)`: Constructor to initialize the memory manager with a specified buffer size.
- `void* allocate(size_t size)`: Allocates a memory block of the specified size.
- `void deallocate(void* ptr)`: Deallocates the memory block pointed to by `ptr`.
- `void* reallocate(void* ptr, size_t newSize)`: Reallocates memory to a new size.
- `size_t size() const`: Returns the total size of the memory buffer.
- `size_t blockSize(void* ptr) const`: Returns the size of the memory block pointed to by `ptr`.

## License
This library is released under the MIT License. See the LICENSE file for more details.