#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Let's declare a type for a "node" of a linked list.

// Since the node needs a way to point to another node,
// the struct needs a pointer to itself.

// The next line will make this possible.
typedef struct Node Node;   // <-- so struct can have a "Node *" member.

typedef struct Node {
    int data;
    Node *next;     // <-- Here's the "Node *" member, called "next".
                    //     It points to another Node.
} Node;

// Abstract-Data-Type time!
// This function creates a new Node and initializes its data member.
void *node_new(int x) {
    Node *node = calloc(sizeof(Node), 1);
    node->data = x;
    return node;
}

int main(void) {
    // Allocate a node.
    Node *node = node_new(42);

    printf("%d\n", node->data);

    return 0;
}
