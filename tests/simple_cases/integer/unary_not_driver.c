int f(int value);

int main() {
    // Test cases
    if (f(0) != 1) {
        return 1; // Indicate failure
    }
    
    if (f(1) != 0) {
        return 1; // Indicate failure
    }

    // Testing with a non-zero value, which should also be considered true
    if (f(2) != 0) {
        return 1; // Indicate failure
    }

    // If all tests pass
    return 0; // Success
}
