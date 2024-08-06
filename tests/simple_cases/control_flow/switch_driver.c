#include <stdio.h>

int switch_test(int x);

int main()
{
    if (switch_test(1) != 100) return 1;
    if (switch_test(2) != 200) return 2;
    if (switch_test(3) != 300) return 3;
    if (switch_test(0) != 0) return 4;
    return 0;
}
