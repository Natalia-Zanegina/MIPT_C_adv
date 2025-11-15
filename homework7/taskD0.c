/*Отсортировать слова

Дана строка, состоящая из английских букв и пробелов. В конце строки символ точка. Все слова разделены одним
пробелом. Необходимо составить из слов односвязный список и упорядочить по алфавиту. Список необходимо удалить 
в конце программы. Для сравнение строк можно использовать strcmp. Необходимо использовать данную структуру 
организации списка:
struct list {
    char word[20];
    struct list *next;
}
Необходимо реализовать односвязный список и обслуживающие его функции:
    add_to_list
    swap_elements
    print_list
    delete_list

Examples:

Input
efg abcd zzz.
Output
abcd efg zzz

Input
fffff kkkkkk a.
Output
a fffff kkkkkk
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 20

typedef struct list {
    char word[20];         
    struct list *next;
} list;

void add_to_list(list **head, char *w){
    list *new = malloc(sizeof(list));
  
    strncpy(new->word, w, sizeof(new->word) - 1);
    new->word[sizeof(new->word) - 1] = '\0';
    new->next = NULL;

    if(!*head)      
        *head = new;
    else{
        list *p = *head;
        while (p->next) 
            p = p->next;

        p->next = new;
    }
}

void swap_elements(list *a, list *b){
    char temp[sizeof(list)];
    strcpy(temp, a->word);
    strcpy(a->word, b->word);
    strcpy(b->word, temp);
}

void print_list(list *head){
    while (head){
        printf("%s ", head->word);
        list *next = head->next;
        head = next;
    }
    printf("\n");
}

void delete_list(list *head){
    while (head){
        list *next = head->next;
        free(head);
        head = next;
    }
}

void sort_list(list *head){
    if(!head) 
        return;
    int swapped;
    do{
        swapped = 0;
        for (list *p = head; p->next; p = p->next) {
            if(strcmp(p->word, p->next->word) > 0){
                swap_elements(p, p->next);
                swapped = 1;
            }
        }
    } while (swapped);
}

int main(void){
    list *l = NULL;
    char w[MAX_SIZE];

    while (scanf("%19s", w) == 1){

        char *dot = strchr(w, '.');       
        if(dot){
            *dot = '\0';
            if (dot != w)                  
                add_to_list(&l, w);
            break;
        } else{
            add_to_list(&l, w);
        }
    }

    sort_list(l);
    print_list(l);
    delete_list(l);
    return 0;
}