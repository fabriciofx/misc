#include <stdio.h>

typedef int i32;
typedef unsigned char byte;

typedef union _Int32 Int32;

union _Int32
{
    i32 value;
    byte bytes[4];
};

#define int32_new(o) ((Int32)(o))
#define int32_value(o) ((o).value)

int
main(void)
{
    i32 a = 20;
    Int32 b = int32_new(30);

    printf ("size: %lu\n", sizeof (Int32));
    printf ("value: %d\n", int32_value(b));
    
    return 0;
}
