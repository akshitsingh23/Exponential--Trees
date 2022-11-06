#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node_Tree node;
typedef struct node_binary bnode;

struct Node_Tree
{
    int level;
    int count;
    node **child;
    int data[];
};

struct node_binary
{
    int key;
    bnode *left;
    bnode *right;
};

int binary_search_tree(node *ptr, int element)
{
    if (ptr->count == 0)
        return 0;
    if (element > ptr->data[ptr->count - 1])
        return ptr->count;

    int start = 0;
    int end = ptr->count - 1;
    int mid = start + (end - start) / 2;

    while (start < end)
    {
        if (element > ptr->data[mid])
            start = mid + 1;
        else
            end = mid;

        mid = start + (end - start) / 2;
    }

    return mid;
}

node *createNode_tree(const int level)
{
    if (level <= 0)
        return NULL;

    /* Allocate node with 2**(level-1) integers */
    node *pNewNode = (node *)malloc(sizeof(node) + sizeof(int) * (1 << (level - 1)));
    memset(pNewNode->data, 0, sizeof(int) * (1 << (level - 1)));

    /* Allocate 2**level child node pointers */
    pNewNode->child = (node **)malloc(sizeof(node *) * (1 << level));
    memset(pNewNode->child, 0, sizeof(int) * (1 << level));

    pNewNode->count = 0;
    pNewNode->level = level;

    return pNewNode;
}
void insert_tree(node *root, int element)
{
    node *ptr = root;
    node *parent = NULL;
    int i = 0;

    while (ptr != NULL)
    {
        int level = ptr->level;
        int count = ptr->count;
        i = binary_search_tree(ptr, element);

        if (count < (1 << (level - 1)))
        {
            for (int j = count; j >= i + 1; --j)
                ptr->data[j] = ptr->data[j - 1];

            ptr->data[i] = element;
            ++ptr->count;
            return;
        }

        parent = ptr;
        ptr = ptr->child[i];
    }

    parent->child[i] = createNode_tree(parent->level + 1);
    insert_tree(parent->child[i], element);
}

void InOrderTrace(node *root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < root->count; ++i)
    {
        if (root->child[i])
            InOrderTrace(root->child[i]);
        printf("%d\n", root->data[i]);
    }

    if (root->child[root->count])
        InOrderTrace(root->child[root->count]);
}

bnode *search(bnode *root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

bnode *insert(bnode *root, int key)
{
    if (!root)
    {
        // Insert the first node, if root is NULL.
        bnode *ptr = (bnode *)malloc(sizeof(bnode));
        return ptr;
    }

    // Insert data.
    if (key > root->key)
    {
        // Insert right node data, if the 'value'
        // to be inserted is greater than 'root' node data.

        // Process right nodes.
        root->right = Insert(root->right, key);
    }
    else if (key < root->key)
    {
        // Insert left node data, if the 'value'
        // to be inserted is smaller than 'root' node data.

        // Process left nodes.
        root->left = Insert(root->left, key);
    }

    // Return 'root' node, after insertion.
    return root;
}

void Inorder(bnode *root)
{
    if (!root)
    {
        return;
    }
    Inorder(root->left);
    printf("%d\n", root->key);
    Inorder(root->right);
}



int main()
{
    node *pRoot = createNode(1);

    for (int i = 0; i < 10000; ++i)
    {
        insert(pRoot, rand());
    }

    InOrderTrace(pRoot);
}