/*************************************************************************
 > File Name: sortTree.c
 > What I should do is fighting !!! 
 > hgg 
 > Created Time: 2016年03月19日 星期六 22时54分37秒
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
typedef int ElemType;
typedef struct _Node {
    struct _Node *left;
    struct _Node *right;
    struct _Node *parent;
    ElemType data;
}Node;
typedef Node *Tree;
Tree create(ElemType *arr, size_t len);
bool insert(Tree t, ElemType va);
Node *buy_node(ElemType);
void mid_trav(Tree tree);
bool insert(Node *root, ElemType data);
void destory(Tree root);
///////////////////////////////////////////////////
Node *buy_node(ElemType data){
    Node *tmp = (Node *)malloc(sizeof(Node));
    assert (tmp != NULL);
    memset(tmp, 0, sizeof(Node));
    tmp->data = data;
    return tmp;
}
void destory(Tree tree){
    if (tree != NULL){
        destory(tree->left);
        destory(tree->right);
        free(tree);
    }
}
bool insert(Node *root, ElemType data) {
    Node *prev = root;
    while (root != NULL) {
        prev = root;
        if (root->data > data) {
            root = root->left;
        }
        else if (root->data < data) {
            root = root->right;
        }
        else return false;
    }
    if (prev->data > data) {
        prev->left = buy_node(data);
    }
    else {
        prev->right = buy_node(data);
    }
    return true;
}
Tree create(ElemType *arr, size_t len){
    Node *_new = buy_node(arr[0]);
    for (size_t i=1; i<len; ++i) {
        insert(_new, arr[i]);
    }
    return _new;
}
void mid_trav(Tree tree){
    if (tree != NULL) {
        mid_trav(tree->left);
        printf("%d  ", tree->data);
        mid_trav(tree->right);
    }
}
int main(){
    Tree t;
    ElemType arr[] = {1,2,3,4,100, 99, 88, 36, 18, 288};
    t = create(arr, sizeof(arr)/sizeof(arr[0]));
    mid_trav(t);
    destory(t);
    return 0;
}
