#include <stdio.h>
#include <x86intrin.h>

char*
get_cpu_name()
{
    unsigned int data[4] = { 0 };

    _asm
    {
        cpuid;
        mov data[0], ebx;
        mov data[4], edx;
        mov data[8], ecx;
    }
    return ((char*) data);
}

int
main(void)
{
    printf("CPU: %s\n", get_cpu_name());
    return 0;
}
