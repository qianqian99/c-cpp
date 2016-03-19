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


void mid_thread_noglobal(Node *root, Node **pprev){
    if (root != NULL){
        mid_thread_noglobal(root->left->child, pprev);

        if (root->left->child == NULL){
            root->left->child = *pprev;
            root->left->tag = LINK;
        }
        if (*pprev != NULL && (*pprev)->right->child == NULL){
            (*pprev)->right->child = root;
            (*pprev)->right->tag = LINK;
        }
        *pprev = root;

        mid_thread_noglobal(root->right->child, pprev);
    }
}
Node *find_left(Node *root){
    while (root != NULL && root->left->tag == CHILD){
        root = root->left->child;
    }
    return root;
}
void MidThread(Node *root){
    if (root != NULL){
        void *func[] = {mid_thread, mid_thread_noglobal};
        int num = 0;
        printf("\nInput 1 or 0 to call func\n");
        scanf("%d", &num);
        Node *tmp = NULL;
        switch (num){
            case 0:((void (*)(Node *))func[0])(root); ptr->right->tag = LINK; ptr=NULL;break;
            case 1:((void (*)(Node *, Node **))func[1])(root, &tmp); tmp->right->tag=LINK;break;
            default:printf("error\n");break;
        }
    }
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

////////////////////////////////////////////

Node *last_func(Node *);
Node *prev_func(Node *);
void rev_mid_thread_trav(Node *);
void rev_mid_thread_trav(Node *root){
    if (root != NULL){
        root = last_func(root);
        while (root != NULL){
            printf("%c ", root->data);
            root = prev_func(root);
        }
    }
}
Node *last_func(Node *root){
    while (root != NULL && root->right->tag != LINK){
        root = root->right->child;
    }
    return root;
}
Node *prev_func(Node *p){
    if (p->left->tag == LINK){
        p = p->left->child;
    }
    else {
        p = last_func(p->left->child);
    }
    return p;
}

////////////////////////////////////////////////////////////////
//
Node *prev = NULL;
void prev_thread(Node *root){
    if (root != NULL){
        if (root->left->child == NULL){
            root->left->child = prev;
            root->left->tag = LINK;
        }
        if (prev != NULL && prev->right->child == NULL){
            prev->right->child = root;
            prev->right->tag = LINK;
        }
        prev = root;
        if (root->left->tag == CHILD)
        prev_thread(root->left->child);
        if (root->right->tag == CHILD)
        prev_thread(root->right->child);
    }
}

void prev_thread_trav(Node *root){
    while (root != NULL){
        if (root->left->tag == CHILD){
            printf("%c ", root->data);
            root = root->left->child;
        }
        else{
            printf("%c ", root->data);
            root = root->right->child;
        }
    }
}
//////////////////////////////////////////////////////////

Node *last = NULL;
void last_thread(Node *root){
    if (root != NULL){
        last_thread(root->left->child);
        last_thread(root->right->child);

        if (root->left->child == NULL){
            root->left->child = last;
            root->left->tag = LINK;
        }
        if (last != NULL && last->right->child == NULL){
            last->right->child = root;
            last->right->tag = LINK;
        }
        last = root;
    }
}
Node *find_value(Node *root, ElemType val){
    if (root == NULL || val == root->data) return root;
    else {
        Node *tmp = NULL;
        if (root->left->tag != LINK)
        tmp = find_value(root->left->child, val);
        if (tmp != NULL || root->right->tag == LINK) return tmp;
        else 
        return find_value(root->right->child, val);
    }
}
Node *parent(Node *cur, Node *root){
    if (root == NULL || cur == NULL)
        return NULL;
    if ((root->left->child == cur && root->left->tag == CHILD) 
        || (root->right->child == cur && root->right->tag == CHILD))
        return root;
    else {
        Node *tmp = NULL;
        if (root->left->tag != LINK)
        tmp = parent(cur, root->left->child);
        if (tmp != NULL || root->right->tag == LINK) return tmp;
        else return parent(cur, root->right->child);
    }
}
Node *first(Node *root){
    while (root->left->tag != LINK)   
        root = root->left->child;
    if (root->right->tag == LINK)     return root;
    else                              first(root->right->child);
}
Node *next(Node *p, Node*root) {
    if (p->right->tag == LINK) {
        return p->right->child;
    }
    else {
        Node *pa = NULL;
        while (1) {
            pa = parent(p, root);
            if (pa->right->child != p || pa == root) break;
            printf("%c ", pa->data);
            p = pa;
        }
        if (pa != root){
            if (pa->right->tag == CHILD) {
                return first(pa->right->child);
            }
            else {
                printf("%c ", pa->data);
                return pa->right->child;
            }
        }
        else {
            if (pa->right->child == p){
                return root;
            }
            else {
                return first(pa->right->child);
            }
        }

    }
}
void last_thread_trav(Node *root){
    Node *p = first(root);
    for (; p!=root; p=next(p, root)){
        printf("%c ", p->data);
    }
    printf("%c ", p->data);
}

void last_trav(Node *root){
    if (root != NULL){
        last_trav(root->left->child);
        last_trav(root->right->child);
        printf("%c ", root->data);
    }
}

int main(){
    ThreadTree root;
    const char *str = "ABDHM###I##EG###CFK###GL###";
    //const char *str = "ABC###DE##F##";
    root = create_thread_tree(&str);
    last_trav(root);
    last_thread(root);
    printf("\n");
    last_thread_trav(root); 
    return 0;
}

