#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

clock_t e_time;
clock_t b_time;
typedef struct Node node;
struct Node
{
    int level;
    int count;
    node **child;
    int data[];
};

struct node
{
    int key;
    struct node *left, *right;
};

// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        // printf("%d \n", root->key);
        inorder(root->right);
    }
}

/* A utility function to insert
   a new node with given key in
 * BST */
struct node *insert1(struct node *node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert1(node->left, key);
    else if (key > node->key)
        node->right = insert1(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

// EXP TREE
int binary_search(node *ptr, int element)
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

node *createNode(const int level)
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

void insert(node *root, int element)
{
    node *ptr = root;
    node *parent = NULL;
    int i = 0;

    while (ptr != NULL)
    {
        int level = ptr->level;
        int count = ptr->count;
        i = binary_search(ptr, element);

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

    parent->child[i] = createNode(parent->level + 1);
    insert(parent->child[i], element);
}

void InOrderTrace(node *root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < root->count; ++i)
    {
        if (root->child[i])
            InOrderTrace(root->child[i]);
        // printf ("%d\n", root->data[i]);
    }

    if (root->child[root->count])
        InOrderTrace(root->child[root->count]);
}

int main()
{
    FILE *file;
    file = fopen("input.txt", "r");

    node *pRoot = createNode(1);

    struct node *root = NULL;

    root = insert1(root, 1);

    if (file == NULL)
    {
        return;
    }

    int N;
    fscanf(file, "%d", &N);

    int k;
    e_time = clock();
    for (int i = 0; i < N; i++)
    {
        fscanf(file, "%d", &k);
        insert(pRoot, k);
        // insert1(root, k);
    }

    InOrderTrace(pRoot);

    e_time = clock() - e_time;
    double exp_t = (double)e_time / CLOCKS_PER_SEC;

    fclose(file);

    FILE *file1;
    file1 = fopen("file1", "r");
    int N1;
    int k1;
    b_time = clock();
    fscanf(file1, "%d", &N1);

    for (int i = 0; i < N; i++)
    {
        fscanf(file1, "%d", &k1);
        insert1(root, k);
    }

    inorder(root);
    b_time = clock() - b_time;
    double bst_t = (double)b_time / CLOCKS_PER_SEC;
    printf("Expo_tree time is %f\n", exp_t);
    printf("Bin_tree time is %f\n", bst_t);
}