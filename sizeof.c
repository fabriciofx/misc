#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <dirent.h>
#include <stdarg.h>
#include <sys/time.h>
#include <wchar.h>
#include <string.h>

#if defined __x86_64__ && !defined __ILP32__
#   define CPU_REGISTERS_WIDTH 64
#else
#   define CPU_REGISTERS_WIDTH 32
#endif

#define AS_STRING(arg) #arg
#define BYTE_OR_BYTES(size) ((size > 1) ? "s" : "")
#define SHOW(type) type_show(AS_STRING(type), sizeof(type))

static void
type_show(const char *name, long size)
{
    char field[21];
    int len = strlen(name);
    memcpy(field, name, len);
    memset(field + len, '.', 20 - len);
    field[20] = 0;
    printf(
        "%s: %2ld byte%s (%ld bits)\n",
        field,
        size,
        BYTE_OR_BYTES(size),
        size * 8
    );
}

static void
cpu_show()
{
    printf("%-20s: %d bits\n", "CPU registers width", CPU_REGISTERS_WIDTH);
}

static void
primitive_types_show()
{
    SHOW(char);
    SHOW(signed char);
    SHOW(unsigned char);
    SHOW(short int);
    SHOW(signed short int);
    SHOW(unsigned short int);
    SHOW(short);
    SHOW(signed short);
    SHOW(unsigned short);
    SHOW(int);
    SHOW(signed int);
    SHOW(unsigned int);
    SHOW(long int);
    SHOW(signed long int);
    SHOW(unsigned long int);
    SHOW(long);
    SHOW(signed long);
    SHOW(unsigned long);
    SHOW(long long);
    SHOW(signed long long);
    SHOW(unsigned long long);
    SHOW(float);
    SHOW(double);
    SHOW(long double);
}

static void
fast_types_show()
{
    SHOW(int_fast8_t);
    SHOW(uint_fast8_t);
    SHOW(int_fast16_t);
    SHOW(uint_fast16_t);
    SHOW(int_fast32_t);
    SHOW(uint_fast32_t);
    SHOW(int_fast64_t);
    SHOW(uint_fast64_t);
}

static void
other_types_show()
{
    SHOW(void *);
    SHOW(wchar_t);
    SHOW(size_t);
    SHOW(ssize_t);
    SHOW(fpos_t);
    SHOW(time_t);
    SHOW(va_list);
}

int
main(void)
{
    printf("# CPU Information\n");
    printf("---------------------------------------------------------------\n");
    cpu_show();
    printf("\n# Primitive types\n");
    printf("---------------------------------------------------------------\n");
    primitive_types_show();
    printf("\n# Fast types\n");
    printf("---------------------------------------------------------------\n");
    fast_types_show();
    printf("\n# Other types\n");
    printf("---------------------------------------------------------------\n");
    other_types_show();
    return EXIT_SUCCESS;
}
