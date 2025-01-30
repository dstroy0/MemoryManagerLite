#include <MemoryManagerLite.h>

MemoryManager memoryManager(1024); // Create a MemoryManager with 1024 bytes buffer

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect. Needed for native USB port only
    }

    Serial.println("MemoryManagerLite Test");

    // Allocate memory
    void *ptr1 = memoryManager.allocate(100);
    if (ptr1 != nullptr) {
        Serial.println("Allocated 100 bytes");
    } else {
        Serial.println("Failed to allocate 100 bytes");
    }

    // Allocate more memory
    void *ptr2 = memoryManager.allocate(200);
    if (ptr2 != nullptr) {
        Serial.println("Allocated 200 bytes");
    } else {
        Serial.println("Failed to allocate 200 bytes");
    }

    // Deallocate memory
    memoryManager.deallocate(ptr1);
    Serial.println("Deallocated 100 bytes");

    // Reallocate memory
    void *ptr3 = memoryManager.reallocate(ptr2, 300);
    if (ptr3 != nullptr) {
        Serial.println("Reallocated to 300 bytes");
    } else {
        Serial.println("Failed to reallocate to 300 bytes");
    }

    // Print buffer size
    Serial.print("Buffer size: ");
    Serial.println(memoryManager.size());

    // Print block size
    Serial.print("Block size: ");
    Serial.println(memoryManager.blockSize(ptr3));
}

void loop() {
    // Nothing to do here
}