#include <stdio.h>

#define K 26


int main(void)
{
    int n = 0;
    scanf("%d", &n);

    char c;

    while((c = getchar()) != '.')
    {
        if (c >= 'a' && c <= 'z')
            printf("%c", (c - 'a' + n) % K + 'a');
        else if (c >= 'A' && c <= 'Z')
            printf("%c", (c - 'A' + n) % K + 'A');
        else if (c == ' ')
            printf(" ");   
    }
    printf(".\n");
    

}