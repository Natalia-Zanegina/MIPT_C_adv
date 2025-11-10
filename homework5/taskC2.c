/* C2-Польская запись

Необходимо вычислить выражение написанное в обратной польской записи. На вход подается строка состоящая из целых, 
неотрицательных чисел и арифметических символов. В ответ единственное целое число - результат. Более подробно об 
Обратной польской записи числа можно также почитать тут

Examples:
Input
3 4 +.
Output
7
Input
1 2 + 4 × 3 +.
Output
15
Input
100 25 + 25 /.
Output
5
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 255

int st[MAX_STACK_SIZE];
int pst = 0;

void push(int v){    st[pst++] = v; }
int pop(){    return st[--pst]; }

void operate(char c)
{
    int arg1 = pop(), arg2 = pop();
    if(c == '+')
        push(arg1 + arg2);
    else if (c == '-')
        push(arg2 - arg1);
    else if (c == '*')
        push(arg1 * arg2);
    else if (c == '/')
        push(arg2 / arg1);
}

int isDigit(char c){    return ((c >= '0') && (c <= '9'));  }

int isOperation(char c){    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));   }


int main(void)
{
    char c;
    char str[MAX_STACK_SIZE];
    int len = 0;

    while((c = getchar()) != '\n')
        str[len++] = c;

    for (int i = 0; i < len; i++)
    {
        if(isDigit(str[i])){
            int num = 0;
            while (isDigit(str[i])){
                num = num * 10 + str[i] - '0';
                i++;
            }
            push(num);
        }else if(i < len)
        {
            if (isOperation(str[i]))
                operate(str[i]);
        }
    }

    printf("%d\n", pop());
    return 0;
}

