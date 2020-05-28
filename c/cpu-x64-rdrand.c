// cc -O3 -mrdrnd cpu-x64-rdrand.c -o cpu-x64-rdrand

#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>

unsigned long long
cpu_random64()
{
    unsigned long long value;
    int ret;
    do {
        ret = _rdrand64_step(&value);
    } while (ret == 0);
    return value;
}

int
main(void)
{
    printf("rdrand: %llu\n", cpu_random64());
    printf("rdrand: %llu\n", cpu_random64());
    printf("rdrand: %llu\n", cpu_random64());
    printf("rdrand: %llu\n", cpu_random64());
    return 0;
}

