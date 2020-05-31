#include <stdio.h>

#define create(name, value)  __typeof(value) name = (value)

int
main(void)
{
    create(age, 31);
    printf("age: %d\n", age);
    create(name, "fabricio");
    printf("name: %s\n", name);
    return 0;
}
