#include <stdio.h>
#include <oxe/memory.h>
#include <oxe/singly-list.h>

int
main(void)
{
    int a = 1, b = 2, c = 3;
    SinglyList *list = memory_new_zeroed(SinglyList);
    SinglyNode **box = &list->first;
    printf("list: %p\n", list);
    printf("list->first: %p\n", list->first);
    printf("list->last: %p\n", list->last);
    printf("box: %p\n", box);
    printf("*box: %p\n", *box);

    printf("-------------------------------------------\n");

    SinglyNode *node = memory_new_zeroed(SinglyNode);
    node->data = &a;
    node->next = NULL;
    list->first = node;
    list->last = node;

    printf("list: %p\n", list);
    printf("list->first: %p\n", list->first);
    printf("list->last: %p\n", list->last);
    printf("list->first->next: %p\n", list->first->next);
    printf("list->first->data: %p\n", list->first->data);
    printf("*list->first->data: %d\n", *((int*) list->first->data));
    printf("list->last->next: %p\n", list->last->next);
    printf("list->last->data: %p\n", list->last->data);
    printf("*list->last->data: %d\n", *((int*) list->last->data));
    printf("box: %p\n", box);
    printf("*box: %p\n", *box);
    printf("**box: %p\n", **box);

    printf("-------------------------------------------\n");

    node = memory_new_zeroed(SinglyNode);
    node->data = &b;
    node->next = NULL;
    list->first->next = node;
    list->last = node;

    printf("list: %p\n", list);
    printf("list->first: %p\n", list->first);
    printf("list->last: %p\n", list->last);
    printf("list->first->next: %p\n", list->first->next);
    printf("list->first->data: %p\n", list->first->data);
    printf("*list->first->data: %d\n", *((int*) list->first->data));
    printf("list->last->next: %p\n", list->last->next);
    printf("list->last->data: %p\n", list->last->data);
    printf("*list->last->data: %d\n", *((int*) list->last->data));
    printf("box: %p\n", box);
    printf("*box: %p\n", *box);
    printf("**box: %p\n", **box);

    return 0;
}
