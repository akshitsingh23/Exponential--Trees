#include <stdio.h>
#include <stdio.h>



int binary_search(node *ptr, int element)
{
    if (ptr->count == 0) return 0;
    if (element > ptr->data[ptr->count-1]) return ptr->count;   

    int start = 0;
    int end = ptr->count - 1;
    int mid = start + (end - start)/2;

    while (start < end)
    {
        if (element > ptr->data[mid]) 
            start = mid + 1;
        else
            end = mid;

        mid = start + (end - start)/2;
    }

    return mid;
}


node* createNode (const int level)
{
    if (level <= 0) return NULL;

        /* Allocate node with 2**(level-1) integers */
    node* pNewNode = (node *) malloc(sizeof(node) + sizeof(int)*(1 << (level - 1))); 
    memset(pNewNode->data, 0, sizeof(int) * (1 << (level - 1 )));

        /* Allocate 2**level child node pointers */
    pNewNode->child = (node *) malloc(sizeof(node *) (1 << level));
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

        if (count < (1 << (level-1)))
        {
            for(int j = count; j >= i+1; --j)
                ptr->data[j] = ptr->data[j-1];

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
    if (root == NULL) return;

    for (int i = 0; i < root->count; ++i)
    {
        if (root->child[i]) InOrderTrace(root->child[i]);
        printf ("%d\n", root->data[i]);
    }

    if (root->child[root->count]) InOrderTrace(root->child[root->count]);
}


void testdata (void)
{
    node* pRoot = createNode(1);

    for (int i = 0; i < 10000; ++i)
    {
        insert(pRoot, rand());
    }

    InOrderTrace(pRoot);
}
