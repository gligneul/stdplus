#include <stdio.h>

#include <stdplus.h>

int main() {
    int *ptr = mem_new(int);
    *ptr = 10;
    printf("stdplus %d\n", *ptr);
    printf("version: %d.%d\n", STDPLUS_VERSION_MAJOR, STDPLUS_VERSION_MINOR);
    return 0;
}

