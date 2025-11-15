/*Найти брата

В программе описано двоичное дерево:
typedef struct tree{
    datatype key;
    struct tree *left, *right;
    struct tree *parent; //ссылка на родителя
} tree;
Требуется реализовать функцию, которая по ключу возвращает адрес соседнего элемента - брата. Если такого ключа нет 
или у узла нет брата, то необходимо вернуть 0.
Прототип функции:
tree * findBrother(tree *root, int key)

Examples
Input
10 5 15 3 7 13 18 1 6 14 0 3
Output
7
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int key;
    struct tree *left, *right;
    struct tree *parent;
} tree;

void insert(tree **root, int key, tree *pt){
    if(!(*root)){ 
        *root = calloc(1, sizeof(tree));
        (*root)->key = key;
        (*root)->parent = pt;
    } else if(key < (*root)->key)
        insert(&((*root)->left), key, *root);
    else
        insert(&((*root)->right), key, *root);
}

tree *findBrother(tree *root, int key){
    if (!root) 
        return 0;
    if (root->key == key){
        if (!root->parent)
            return 0;
        if (root->parent->left == root)
            return root->parent->right;
        else
            return root->parent->left;
    }
    if (key < root->key)
        return findBrother(root->left, key);
    else
        return findBrother(root->right, key);

}

int main(void)
{
    tree *tr = NULL;
    insert(&tr, 10, NULL);
    insert(&tr, 5, NULL);
    insert(&tr, 15, NULL);
    insert(&tr, 3, NULL);
    insert(&tr, 7, NULL);
    insert(&tr, 13, NULL);
    insert(&tr, 18, NULL);
    insert(&tr, 1, NULL);
    insert(&tr, 6, NULL);
    insert(&tr, 14, NULL);

    printf("%d ", findBrother(tr, 3)->key);
    return 0;
}