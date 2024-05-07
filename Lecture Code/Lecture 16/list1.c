#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Let's make a list of Nodes.

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

// Let's make a two-node linked list.
//
// n1 -------> n2 -------> NULL
//     next        next

int main(void) {
    // Allocate two Nodes.
    Node *n1 = node_new(1);
    Node *n2 = node_new(2);

    // "Point" n1 to n2.
    n1->next = n2;

    // So now we have:
    //
    // n1.data == 1
    // n1.next == n2
    //
    // n2.data == 2
    // n2.next == NULL

    // So n1 points to a list of nodes.
    // Let's print the list!
    Node *n = n1;
    while (n != NULL) {
        printf("%d\n", n->data);

        // Step to the next Node of the linked list.
        n = n->next;
    }

    return 0;
}
