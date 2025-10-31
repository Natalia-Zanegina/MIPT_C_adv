#include <stdio.h>
#include <stdint.h>

int main()
{
    uint32_t N;
    int K;
    scanf("%u %d", &N, &K);
    uint32_t res = (N >> K) | (N << (32 - K));
    printf("%u\n", res);
    return 0;
}