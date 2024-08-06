int add(int a, int b) {
    return a + b;
}

int f() {
    int x = 10;
    int *ptr = &x;
    
    *ptr = add(*ptr, 5);
    
    return *ptr;
}
