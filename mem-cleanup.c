#include <stdlib.h>  
#include <stdio.h>  
  
#define smart __attribute((cleanup(__smart)))  

void __smart(void *p)  
{  
    void **_p = (void**)p;  
  
    printf("free: %p\n", *_p);  
    free(*_p);  
}  
  
void *myalloc(size_t sz)  
{  
    void *ptr;  
  
    if ((ptr = malloc(sz)) == NULL) {  
        fprintf(stderr, "malloc failed.\n");  
        exit(1);  
    }  
    printf("malloc: %p\n", ptr);  
  
    return ptr;  
}  
 
typedef struct _Person Person;

struct _Person
{
    int age;
    char *name;
};

Person* person_new(char *name, int age)
{
    Person* p = myalloc(sizeof(Person));
    p->name = name;
    p->age = age;
    return p;
}

Person* person_new2(char *name, int age)
{
    smart Person* p = myalloc(sizeof(Person));
    p->name = name;
    p->age = age;
    return p;
}

void person_print(Person *person)
{
    printf("[%p] Name: %s, Age: %d\n", person, person->name, person->age);
}

 
int main(int argc, char **argv)  
{  
    smart char *x = myalloc(32);
    {  
        smart int *y = myalloc(64);  
  
        printf("y = %p\n", y);  
    }  
    printf("x = %p\n", x);  
    
    smart Person* p = person_new("fabricio", 40);
    person_print(p);
    printf("[%p] Name2: %s, Age2: %d\n", p, p->name, p->age);

    Person *p3 = person_new2("maria", 20);
    person_print(p3);

    return 0;
}  
