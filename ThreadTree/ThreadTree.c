#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define END '#'
typedef char ElemType;
typedef struct ThreadTreeNode * pNode;
typedef enum{
    CHILD,
    LINK
}Tag;
typedef struct{
    pNode child;
    Tag tag;
}Link;
typedef struct ThreadTreeNode{
    Link *left;
    ElemType data;
    Link *right;
}Node, *ThreadTree;

Node *ptr = NULL;
Node *buy_node(){
    Node *s = (Node *)malloc(sizeof(Node));
    Link *l = (Link *)malloc(sizeof(Link));
    Link *r = (Link *)malloc(sizeof(Link));
    if (s == NULL || l == NULL || r == NULL) exit(0);;
    memset (s, 0, sizeof(Node));
    memset (l, 0, sizeof(Link));
    memset (r, 0, sizeof(Link));
    s->left = l;
    s->right = r;
    return s;
}
Node *create_thread_tree(const ElemType **str){
    Node *s = NULL;
    if (**str != END){
        s = buy_node();
        s->data = **str;
        (*str)++;
        s->left->child = create_thread_tree(str);
        (*str)++;
        s->right->child = create_thread_tree(str);
    }
    return s;
}
void mid_trav(Node *root){
    if (root != NULL){
        mid_trav(root->left->child);
        printf("%c ", root->data);
        mid_trav(root->right->child);
    }
}
void mid_thread(Node *root){
    if (root != NULL){
        mid_thread(root->left->child);
        
        if (root->left->child == NULL){
            root->left->tag = LINK;
            root->left->child = ptr;     //global val
        }
        if (ptr != NULL && ptr->right->child == NULL){
            ptr->right->tag = LINK;
            ptr->right->child = root;
        }
        ptr = root;
        mid_thread(root->right->child);
    }
}
Node *find_left(Node *root){
    while (root != NULL && root->left->tag == CHILD){
        root = root->left->child;
    }
    return root;
}
void mid_thread_trav(Node *root){
    root = find_left(root);
    while (root != NULL){
        printf("%c ", root->data);
        if (root->right->tag == CHILD){
            root = root->right->child;
            root = find_left(root);
        }
        else if(root->right->tag == LINK){
            root = root->right->child;
        }
    }
}
int main(){
    ThreadTree root;
    const char *str = "ABC###DE##F##";
    root = create_thread_tree(&str);
    mid_trav(root);
    mid_thread(root);
    printf("\n");
    mid_thread_trav(root);
    return 0;
}

