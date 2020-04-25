#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>

#define KiB (1024)
#define MiB (1024 * KiB)
#define GiB (1024 * MiB)

void*
memory_alloc(unsigned long int nbytes)
{
    void* memory = malloc(nbytes);
    if (memory == NULL) perror("out of memory");
    return memory;
}

void
memory_dealloc(void* memory)
{
    free(memory);
}

void*
memory_realloc(void* memory, unsigned long int new_nbytes)
{
    void* new_memory = realloc(memory, new_nbytes);
    if (memory == NULL) perror("out of memory");
    return memory;
}

void*
memory_copy(void* dest, const void* source, unsigned long int nbytes)
{
    unsigned char *dst = ((unsigned char*) dest);
    const unsigned char *src = ((const unsigned char*) source);
    while (nbytes--) {
        *dst++ = *src++;
    }
    return dest;
    // return memcpy(dest, source, nbytes);
}

void*
memory_write(void* dest, int data, unsigned long int nbytes)
{
    unsigned char *dst = ((unsigned char*) dest);
    while (nbytes--) {
        *dst++ = ((unsigned char) data);
    }
    return dest;
    // return memset(dest, data, nbytes);
}

void*
memory_clone(const void* memory, unsigned long int nbytes)
{
    void* clone = memory_alloc(nbytes);
    return memory_copy(clone, memory, nbytes);
}

static void
check(void* memory, int data, unsigned long int nbytes)
{
    unsigned char *mem = ((unsigned char *)(memory));
    for (int i = 0; i < nbytes; i++) {
        if (*mem != ((unsigned char) data)) {
            abort();
        }
        mem++;
    }
}

static void
test_alloc_write_copy_dealloc(unsigned long int nbytes)
{
    void* memory1 = memory_alloc(nbytes);
    memory_write(memory1, 'x', nbytes);
    check(memory1, 'x', nbytes);
    void* memory2 = memory_clone(memory1, nbytes);
    check(memory2, 'x', nbytes);
    memory_dealloc(memory1);
    memory_dealloc(memory2);
}

int
main(void)
{
    test_alloc_write_copy_dealloc(0);
    test_alloc_write_copy_dealloc(1);
    test_alloc_write_copy_dealloc(2);
    test_alloc_write_copy_dealloc(3);
    test_alloc_write_copy_dealloc(4);
    test_alloc_write_copy_dealloc(5);
    test_alloc_write_copy_dealloc(6);
    test_alloc_write_copy_dealloc(7);
    test_alloc_write_copy_dealloc(8);
    test_alloc_write_copy_dealloc(9);
    test_alloc_write_copy_dealloc(10);
    test_alloc_write_copy_dealloc(11);
    test_alloc_write_copy_dealloc(12);
    test_alloc_write_copy_dealloc(13);
    test_alloc_write_copy_dealloc(14);
    test_alloc_write_copy_dealloc(15);
    test_alloc_write_copy_dealloc(16);
    test_alloc_write_copy_dealloc(17);
    test_alloc_write_copy_dealloc(18);
    test_alloc_write_copy_dealloc(19);
    test_alloc_write_copy_dealloc(100);
    test_alloc_write_copy_dealloc(4 * KiB);
    test_alloc_write_copy_dealloc(8 * KiB);
    test_alloc_write_copy_dealloc(1000000);
    test_alloc_write_copy_dealloc(1000001);
    test_alloc_write_copy_dealloc(1000002);
    test_alloc_write_copy_dealloc(1000003);
    test_alloc_write_copy_dealloc(1000004);
    test_alloc_write_copy_dealloc(1000005);
    test_alloc_write_copy_dealloc(1000006);
    test_alloc_write_copy_dealloc(1000007);
    test_alloc_write_copy_dealloc(1000008);
    test_alloc_write_copy_dealloc(1000009);
    test_alloc_write_copy_dealloc(1000010);
    test_alloc_write_copy_dealloc(1000011);
    test_alloc_write_copy_dealloc(1000012);
    test_alloc_write_copy_dealloc(1000013);
    test_alloc_write_copy_dealloc(1000014);
    test_alloc_write_copy_dealloc(1000015);
    test_alloc_write_copy_dealloc(1000016);
    test_alloc_write_copy_dealloc(1000017);
    test_alloc_write_copy_dealloc(1000018);
    test_alloc_write_copy_dealloc(1000019);
    test_alloc_write_copy_dealloc(MiB);
    test_alloc_write_copy_dealloc(100 * MiB);
    return 0;
}
