/*
Максимальный блок

Описана структура данных

typedef struct list {
uint64_t address;
size_t size;
char comment[64];
struct list *next;
} list;

Требуется реализовать только одну функцию, которая в данном списке находит адрес блока памяти занимающий
больше всего места.
Адрес хранится в поле address, поле size - соответствующий размер данного блока. 
Если список пустой, то функция должна возвращать 0. Если есть несколько таких блоков, то вернуть адрес любого из них.

Прототип функции:
uint64_t findMaxBlock(list *head)

Examples
Input
3
	  140525067852320 10
	  140525067852350 30
	  140525067852900 100
Output
140525067852900
*/
#include <stdint.h>
#include <stddef.h>

typedef struct list
{
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

uint64_t findMaxBlock(list *head)
{

    uint64_t maxBlockAddress = 0;
    size_t maxSize = 0;

    for (list *b = head; b != NULL; b = b->next)
    {
        if (maxSize < b->size)
        {
            maxSize = b->size;
            maxBlockAddress = b->address;
        }
    }
    return maxBlockAddress;
}