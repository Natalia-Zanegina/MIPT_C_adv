#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);

    int res = 0;

    for (int i = 0; i < n; i++)
    {
        int res_prev = res;
        scanf("%d", &res);
        res ^= res_prev;
    }

    printf("%d\n", res);

    return 0;
}