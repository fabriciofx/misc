/**
 * cc -fms-extensions -Wno-microsoft-anon-tag -o anon-structs anon-structs.c -lm
 */
#include <math.h>
#include <stdio.h>

typedef struct point
{
    double x, y;
} point;

typedef struct
{
    union
    {
        struct point;
        point p2;
    };
    double z;
} threepoint;

double
length(point p)
{
    return sqrt(p.x * p.x + p.y * p.y);
}

double
threelength(threepoint p)
{
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

int
main(void)
{
    threepoint p = { .x = 3, .y = 0, .z = 4 };
    printf("p is %g units from the origin\n", threelength(p));
    double xylength = length(p.p2);
    printf(
        "Its projection onto the XY plane "
        "is %g units from the origin\n",
        xylength
    );
    return 0;
}
