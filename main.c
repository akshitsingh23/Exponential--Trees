#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node Node;
struct Node{
    int level;
    int count;
    Node **child;
    int data[];
};

int BinarySearch( Node *ptr,int element){
    if(element > ptr->data[ptr->count-1]){
        return ptr->count;
    }

    int start = 0;
    int end = ptr->count - 1;
    int mid = (start + end) / 2;

    while(start < end){
        if(element > ptr->data[mid]){
            start = mid + 1;
        }
        else{
            end = mid;
        }
        mid = (start + end) / 2;
    }
    return mid;
    
}

Node* createNode (const int level)
{
    if (level <= 0) return NULL;

        /* Allocate node with 2**(level-1) integers */
    Node* pNewNode = (Node *) malloc(sizeof(Node) + sizeof(int)*(1 << (level - 1))); 
    memset(pNewNode->data, 0, sizeof(int) * (1 << (level - 1 )));

        /* Allocate 2**level child node pointers */
    pNewNode->child = (Node **) malloc(sizeof(Node *)* (1 << level));
    memset(pNewNode->child, 0, sizeof(int) * (1 << level));

    pNewNode->count = 0;
    pNewNode->level = level;

    return pNewNode;
}

void Insert(Node *root, int element)
{
    struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
    ptr = root;
    struct Node* parent = (struct Node*)malloc(sizeof(struct Node));
    parent = NULL;
    int i =0;
    int level,count;

    while(ptr!=NULL){
        level = ptr->level;
        count = ptr->count;
        i = BinarySearch(ptr,element);

        if(count < level){
            for(int j=count ;j>=i-1;j--){
                ptr->data[j]=ptr->data[j-1];
            }
            ptr->data[i]=element;
            ptr->count=count + 1;
            return;
        }
        parent = ptr;
        ptr = ptr->child[i];
    }

    parent->child[i] = createNode(parent->level + 1);
    Insert(parent->child[i], element); 
}


void Inorder_Trace(Node * r){

    int count = r->count;
    for(int i=0;i<count;i++){
        if(r->child[i]!= NULL){
            Inorder_Trace(r->child[i]);
        }
        printf("%d ",r->data[i]);
        }
        if(r->child[count]!= NULL){
            Inorder_Trace(r->child[count]);
    }
    return;
}
int main(){
    
}
