#include <stdio.h>

int
main(void)
{
    FILE* fp = fopen("hello.txt", "r");
    while(!feof(fp)) {
        printf("%c", fgetc(fp));
    }
    fclose(fp);
    return 0;
}
