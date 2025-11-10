/* C1-Префикс и суффикс

На стандартном потоке ввода задаются две символьные строки, разделённые символом перевода строки. Каждая из строк 
не превышает по длине 104. В строках не встречаются пробельные символы. На стандартный поток вывода напечатайте 
два числа, разделённых пробелом: первое число — длина наибольшего префикса первой строки, являющегося суффиксом 
второй; второе число — наоборот, длина наибольшего суффикса первой строки, являющегося префиксом второй. Сравнение 
символов проводите с учётом регистра (т.е. символы 'a' и 'A' различны).

Examples:
Input
don't_panic
nick_is_a_mastodon
Output
3 3
Input
monty_python
python_has_list_comprehensions
Output
0 6
*/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#define MAX_SIZE 10000

int min(int a, int b){
    return a < b ? a : b;
}

int max(int z[], int n){
    int max = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (z[i] > max)
            max = z[i];  
    }
    return max;
}

void zFunc(char *s, int z[]){
    int n = strlen(s);

    for (int i = 0, l = 0, r = 0; i < n; ++i)
    {
        if(i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if(i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;  
    }   
}

int max_pref(char *str1, char *str2){
    char s[MAX_SIZE + MAX_SIZE] = {0};
    int z[MAX_SIZE + MAX_SIZE] = {0};
    size_t str1len = strlen(str1);
    size_t str2len = strlen(str2);
    if(!str1len || !str2len)
        return 0;
    sprintf(s, "%s#%s", str1, str2);
    zFunc(s, z);
    int num_max = max(z + str2len, str1len);
    size_t size = strlen(s);
    int result = 0;
    for (size_t i = 0; i < size; i++)
    {
        if((z[i] == num_max) && (i + num_max == size))
            result = size - i;
    }
    return result;
}


int main(void)
{
    char str1[MAX_SIZE];
    char str2[MAX_SIZE];
    scanf("%s", str1);
    scanf("%s", str2);

    printf("%d %d\n", max_pref(str1, str2), max_pref(str2, str1)); 
    return 0;
}
