#include <stdio.h>
#include <string.h>

int
main(void)
{
    printf("cmp NULL, NULL, 0: %d\n", memcmp(NULL, NULL, 0));
    printf("cmp \"\", \"\", 1: %d\n", memcmp("", "", 1));
    printf("cmp \"\", \"a\", 1: %d\n", memcmp("", "a", 1));
    printf("cmp \"a\", \"\", 1: %d\n", memcmp("a", "", 1));
    printf("cmp \"a\", \"a\", 1: %d\n", memcmp("a", "a", 1));
    return 0;
}
