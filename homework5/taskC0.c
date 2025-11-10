/* C0-Вычеркивание

Сколько различных трехзначных чисел можно получить из заданного натурального N, вычеркивая цифры из его десятичной 
записи?

Examples:
Input
1111111111111111111111111
Output
1
*/
// #include <stdio.h>
// #include <stdint.h>
// #include <inttypes.h>
// #include <string.h>
// #include <stdlib.h>

// uint64_t p = 10;
// uint64_t getHash(char *str, size_t len) {
//     uint64_t hash = 0;
//     char c;
//     for(size_t i = 0; i < len; i++) {
//         c = str[i]; 
//         hash *= p; 
//         hash += (c - '0'); 
//     }
//     return hash;
// }

// int cmphashes(const void* a, const void* b){
//     return *(int*)a < *(int*)b ? -1 : 1;
// }

// int main(void)
// {
//     char num[100];
//     scanf("%s", num);
   
//     uint64_t ht[100], p_pow = 1;
//     size_t lens = 3, lent = strlen(num);


//     for (size_t i = 1; i < lens; i++)
//         p_pow *= p;
    
//     ht[0] = getHash(&num[0], lens);

//     size_t i;
    
//     for (i = 1; i < lent - lens + 1; i++)
//         ht[i] = (ht[i-1] % p_pow) * p + num[lens + i - 1] - '0';

//     qsort(ht, i, sizeof(uint64_t), cmphashes);

//     int result = 0;
//     for (int j = 0; j < i; j++) {
//         if (j == 0 || ht[j] != ht[j - 1])
//             result++;     
//     }
//     printf("%d\n", result);
// }
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char number[1000];
    scanf("%s", number);
    int len = strlen(number);
    
    int result = 0, not_unique[1000] = {0};
    for (int i = 0; i < len; i++) 
    {
        for (int j = i + 1; j < len; j++) 
        {
            for (int k = j + 1; k < len; k++)
            {
                int n = (number[i] - '0') * 100 + (number[j] - '0') * 10 + (number[k] - '0');
                if (n > 99 && !not_unique[n]) 
                {
                    not_unique[n] = 1;
                    result++;

                    printf("%d - %d\n", result, n);
                }
            }
        }
    }
    
    printf("%d\n", result);
    return 0;
}