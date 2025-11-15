/*Вид сверху

В программе описана структура для хранения двоичного дерева:
typedef struct tree{
    datatype key;
    struct tree *left, *right;
} tree;
Необходимо реализовать функцию, которая печатает вид дерева сверху. Функция должна строго соответствовать прототипу:
void btUpView(tree *root)

Examples

Input
10 5 15 3 7 13 18 1 6 14 0
Output
1 3 5 10 15 18
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int key;
    struct tree *left, *right;
} tree;

void insert(tree **root, int key){
    if(!(*root)){ 
        *root = calloc(1, sizeof(tree));
        (*root)->key = key;
    } else if(key < (*root)->key)
        insert(&((*root)->left), key);
    else
        insert(&((*root)->right), key);
}

void inorder_left(tree *root){
    if(root == NULL)
        return;
    if(root->left)
        inorder_left(root->left);
    printf("%d ", root->key);
}

void btUpView(tree *root){
    inorder_left(root);
    while (root && root->right){
        root = root->right;
        printf("%d ", root->key);
    }
}

int main(void)
{
    tree *tr = NULL;
    insert(&tr, 10);
    insert(&tr, 5);
    insert(&tr, 15);
    insert(&tr, 3);
    insert(&tr, 7);
    insert(&tr, 13);
    insert(&tr, 18);
    insert(&tr, 1);
    insert(&tr, 6);

    btUpView(tr);
    return 0;
}