#include <stdio.h>

// Bitwise NOT operation
int bitwise_not(int x);

int main() {
    // Test if bitwise_not correctly inverts the bits of 0xFFFF
    // The expected result of inverting 0xFFFF is 0xFFFF0000 in a 32-bit system
    // However, due to sign extension and the fact that literals are considered ints,
    // the actual comparison needs to account for the fact that the high bits will be set.
    // We use unsigned int for comparison to avoid issues with sign extension.
    unsigned int result = bitwise_not(0xFFFF);
    unsigned int expected = 0xFFFF0000; // Adjust this value based on your system/expectation

    // Return 0 if the test passes, 1 if it fails
    return !(result == expected);
}
