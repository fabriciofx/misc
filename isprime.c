// cc -g -o isprime isprime.c

#include <stdbool.h>
#include <stdio.h>

bool
is_prime(int n)
{
    for(int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int
main(void)
{
    for (int i = 2; i < 100000; i++) {
        if (is_prime(i)) {
            printf("%d is prime!\n", i);
        }
    }
    return 0;
}
