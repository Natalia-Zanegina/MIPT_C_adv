#include <stdio.h>

int main()
{
    int n, a, max = -2147483648, res = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        if (a > max)
        {
            max = a;
            res = 1;
        }
        else if (a == max)
        {
            res++;
        }
    }
    printf("%d\n", res);
    return 0;
}