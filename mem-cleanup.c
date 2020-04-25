#include <stdlib.h>  
#include <stdio.h>  
  
#define autofree __attribute((cleanup(__autofree)))  

typedef struct _Person Person;

struct _Person
{
    int age;
    char *name;
};

void __autofree(void *p)  
{  
    void **_p = (void**)p;  
  
    printf("free -> %p\n", *_p);  
    free(*_p);  
}  
  
void *myalloc(size_t sz)  
{  
    void *ptr;  
  
    if ((ptr = malloc(sz)) == NULL) {  
        fprintf(stderr, "malloc failed.\n");  
        exit(1);  
    }  
    printf("malloc -> %p\n", ptr);  
  
    return ptr;  
}  
  
int main(int argc, char **argv)  
{  
    autofree char *x = myalloc(32);
    {  
        autofree int *y = myalloc(64);  
  
        printf("y = %p\n", y);  
    }  
    printf("x = %p\n", x);  
  
    return 0;
}  
