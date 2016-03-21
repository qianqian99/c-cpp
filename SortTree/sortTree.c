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
Node *find_value(Tree tree, ElemType val);
Node *search_value(Tree tree, ElemType val);
Node *search(Node *root, ElemType val);
void mid_trav2(Tree tree);
///////////////////////////////////////////////////
Node *find_value(Tree tree, ElemType val){
    Node *root = tree;
    while (root != NULL && root->data != val){
        if (root->data > val) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return root;
}
Node *search(Node *root, ElemType val) {
    if (root->data == val){
        return root;
    }
    if (root->data > val ){
        return search(root->left, val);
    }
    else {
        return search(root->right, val);
    }
}
Node *search_value(Tree tree, ElemType val) {
    if (tree != NULL){
        return search(tree, val);
    }
    return NULL;
}
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
        prev->left->parent = prev;
    }
    else {
        prev->right = buy_node(data);
        prev->right->parent = prev;
    }
    return true;
}
Tree create(ElemType *arr, size_t len){
    Node *_new = buy_node(arr[0]);
    _new->parent = NULL;
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
////////////////////////////////////////
//非递归遍历

Node *first(Node *root){
    if (root == NULL) return NULL;
    while (root->left != NULL){
        root = root->left;
    }
    return root; 
}
Node *next(Node *root){
    if (root->right != NULL) return first(root->right);
    else {
            Node *prev = root->parent;
        while (prev != NULL && root != prev->left){
            root = prev;
            prev = prev->parent;
        }
        return prev;
    }
}
void mid_trav2(Tree tree){
    Node *p = first(tree);
    while (p != NULL){
        printf("%d ", p->data);
        p = next(p);
    }
}

////////////////////////////////////////
//void remove_leaf(Node *pa, Node *p){
//    if (pa->left == p) pa->left = NULL;
//    else pa->right = NULL;
//    free(p);
//}
//void remove_one(Node *pa, Node *p) {
//    if (pa->left == p) {
//        if (p->left != NULL) {
//            pa->left = p->left;
//            p->left->parent = pa;
//            free(p);
//        }
//        else if (p->right != NULL) {
//            pa->left = p->right;
//            p->right->parent = pa;
//            free(p);
//        }
//        else {
//            pa->left = NULL;
//        }
//    }
//    else {
//        if (p->left != NULL){
//            pa->right = p->left;
//            p->left->parent = pa;
//            free(p);
//        }
//        else if (p->right != NULL){
//            p->right = p->right;
//            p->right->parent = pa;
//            free(p);
//        }
//        else {
//            pa->right = NULL;
//        }
//    }
//}
//Node *next(Node *p){
//    if (p == NULL) return p;
//    if (p->right != NULL) {
//        p = p->right;
//        while (p->left != NULL){
//            p = p->left;
//        }
//        return p;
//    }
//    else {
//        Node *pa = p->parent;
//        while (pa != NULL && pa->left != p) {
//            p = pa;
//            pa = pa->parent;
//        }
//        return pa;
//    }
//
//}
//single branch remove root
int main(){
    Tree t;
    ElemType arr[] = {1,2,3,4,100, 99, 88, 36, 18, 288};
    t = create(arr, sizeof(arr)/sizeof(arr[0]));
    mid_trav2(t);
    destory(t);
    return 0;
}
