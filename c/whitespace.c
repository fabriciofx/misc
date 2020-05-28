#include <stdio.h>
#include <string.h>
#include <assert.h>

void
look(char *str)
{
    printf("'%s' has size %lu\n", str, strlen(str));
    if (str == NULL) {
        printf("\"%s\" is equal to NULL\n");
    } else {
        printf("'\"\"' is not equal to NULL\n");
    }
    printf("'%c'\n", *str);
}
 
int
main(void)
{
    look("");
    look("a");
    return 0;
}
