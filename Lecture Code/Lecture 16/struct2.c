#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// We need to free() everything that gets calloc()'ed.
// Read about node_delete() below.

typedef struct Node Node;

typedef struct Node {
    int data;
    Node *next;
} Node;

void *node_new(int x) {
    Node *node = calloc(sizeof(Node), 1);
    node->data = x;
    return node;
}

// Free a Node and set the pointer of the freed Node to NULL.
// So call this function as node_delete(&pnode);
//                                      ^-- address of the Node pointer
//
// Why do we set *pnode to NULL???
//
// Because after the Node has been freed, its memory might be used for
// something else.  And if we were to do so, like node->data = 3, then
// really we would be writing 3 into some other data structure!
// So setting *pnode to NULL ensures that any subsequent, buggy attempt
// to write to node->data will crash the program immediately, revealing
// that we have a bug to fix.
void node_delete(Node **pnode) {
    //                  ^^^^^^--- pnode is a pointer to a pointer to a Node
    //                 ^^^^^^^--- *pnode is a pointer to a Node
    //                ^^^^^^^^--- **pnode is a Node

    // free the pointer to the Node
    free(*pnode);

    // set the pointer to the Node to NULL
    *pnode = NULL;
}

int main(void) {
    // Allocate a Node.
    Node *node = node_new(42);

    printf("%d\n", node->data);

    // Free the Node.
    node_delete(&node);

    return 0;
}
