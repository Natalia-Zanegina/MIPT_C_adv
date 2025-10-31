#include <stdio.h>
#include <stdint.h>


int main(int argc, char const *argv[])
{
    uint32_t num, temp, res;
    scanf("%u", &num);
    temp = ~(num >> 24) << 24;
    res = num << 8 >> 8 | temp;

    printf("%u\n", res);
    return 0;
}