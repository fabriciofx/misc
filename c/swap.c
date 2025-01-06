#include <stdio.h>

int
main()
{
    int x, y;

    printf("x: ");
    scanf("%d", &x);
    printf("y: ");
    scanf("%d", &y);
    printf("x, y: %d, %d\n", x, y);
    x += y;
    y = x - y;
    x -= y;
    printf("x, y: %d, %d\n", x, y);

    return 0;
}
