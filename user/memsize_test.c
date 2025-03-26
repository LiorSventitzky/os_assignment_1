
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int sizeB = memsize();
    printf("Memory before allocation: %d bytes\n", sizeB);
    void *ptr = malloc(20000);
    int sizeA = memsize();
    printf("Memory after allocation: %d bytes\n", sizeA);
    free(ptr);
    int sizeF = memsize();
    printf("Memory after free allocation: %d bytes\n", sizeF);
    exit(0);
}
