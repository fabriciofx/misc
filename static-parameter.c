#include <stdio.h>

void
no_static_param(char *s)
{
    printf("no static param: %s\n", s);
}

void
static_param(char s[static 1])
{
    printf("static param: %s\n", s);
}

int
main(void)
{
    char *x = NULL;
    no_static_param("joao");
    static_param("pedro");
    static_param("");
    static_param(x);
    no_static_param(NULL);
    return 0;
}
