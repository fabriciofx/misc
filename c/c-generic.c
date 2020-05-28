#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char Byte;
typedef union { short int value; Byte byte[2]; } i16;
typedef union { unsigned short int value; Byte byte[2]; } u16;
typedef union { int value; Byte byte[4]; } i32;
typedef union { unsigned int value; Byte byte[4]; } u32;
typedef union { long long value; Byte byte[8]; } i64;
typedef union { unsigned long long value; Byte byte[8]; } u64;
typedef struct { char* chars; unsigned long long length; } String;

// #define $(value) { value }

#define $(value) { \
    _Generic(value, \
        int: value, \
        char*: value, \
        const char*: value, \
        char[sizeof(value)]: value, \
        const char[sizeof(value)]: value \
)}

static void
print_i32(i32 i)
{
    printf ("i32 size: %lu\n", sizeof(i32));
    printf ("i32 value: %d\n", i.value);
    printf ("i32 byte[0]: %d\n", i.byte[0]);
    printf ("i32 byte[1]: %d\n", i.byte[1]);
    printf ("i32 byte[2]: %d\n", i.byte[2]);
    printf ("i32 byte[3]: %d\n", i.byte[3]);
}

static void
print_string(String s)
{
    printf(" Chars: %s\n", s.chars);
    printf("Length: %llu\n", s.length);
}

int
main(void)
{
    // i32 ipv4 = { 10000 };
    // String nome = { "fabricio", strlen("fabricio") };
    // i32 ipv4 = {_Generic(10000, int: 10000)};
    // String nome = {
    //     _Generic("fabricio",
    //         char*: "fabricio",
    //         const char*: "fabricio",
    //         const char[sizeof("fabricio")]: "fabricio",
    //         char[sizeof("fabricio")]: "fabricio"
    //     )
    // };
    i32 ipv4 = $(10000);
    String nome = $("fabricio");

    print_i32(ipv4);
    // print_string(nome);

    return 0;
}
