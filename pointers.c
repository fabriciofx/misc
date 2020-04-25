#include <stdio.h>
#include <stdlib.h>

struct node {
    int n;
    struct node *next;
};


int
main(void)
{
    printf("+------------+-----------------+-----------------+\n");
    printf("| %-10s | %-15s | %-15s |\n", "name", "address", "content");
    printf("+------------+-----------------+-----------------+\n");
    
    int a = 10;
    int *pa = &a;
    int **ppa = &pa;

    printf("| %-10s | %-15p | %-15d |\n", "a", &a, a);
    printf("| %-10s | %-15p | %-15p |\n", "pa", &pa, pa);
    printf("| %-10s | %-15p | %-15d |\n", "*pa", &(*pa), (*pa));
    printf("| %-10s | %-15p | %-15p |\n", "ppa", &ppa, ppa);
    printf("| %-10s | %-15p | %-15p |\n", "*ppa", &(*ppa), *ppa);
    printf("| %-10s | %-15p | %-15d |\n", "**ppa", &(**ppa), **ppa);
    
    printf("+------------+-----------------+-----------------+\n");

    struct node *node = malloc(sizeof(struct node));
    node->n = 100;
    node->next = NULL;
    
    printf("| %-10s | %-15p | %-15p |\n", "node", &node, node);
    printf("| %-10s | %-15p | %-15d |\n", "*node", &(*node), *node);
    printf("| %-10s | %-15p | %-15d |\n", "*(node+1)", &(*(node + 1)), *(node + 1));
    printf("| %-10s | %-15p | %-15d |\n", "node->n", &(node->n), node->n);
    printf("| %-10s | %-15p | %-15p |\n", "node->next", &(node->next), node->next);
    
    printf("+------------+-----------------+-----------------+\n");
    
#if 0
    struct node *list = node;
    printf("| %-10s | %-15p | %-15p |\n", "node", &node, node);
    printf("| %-10s | %-15p | %-15d |\n", "node->n", &(node->n), node->n);
    printf("| %-10s | %-15p | %-15p |\n", "node->next", &(node->next), node->next);
    printf("| %-10s | %-15p | %-15p |\n", "list", &(list), list);
    printf("| %-10s | %-15p | %-15d |\n", "*list", &(*list), *list);
#endif
    return 0;
}
