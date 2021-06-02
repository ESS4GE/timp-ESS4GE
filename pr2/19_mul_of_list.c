#include <stdio.h>

int main()
{
    int n, i, x;
    long int incr = 1;
    (void)scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        (void)scanf("%d", &x);
        incr *= x;
    }
    printf("%ld", incr);
    return 0;
}