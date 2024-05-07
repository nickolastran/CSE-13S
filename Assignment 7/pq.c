#include "pq.h"

#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *queue = malloc(sizeof(PriorityQueue));
    if (queue == NULL) {
        return NULL;
    }
    queue->list = NULL;
    return queue;
}

void pq_free(PriorityQueue **q) {
    free(*q);
    *q = NULL;
}

bool pq_is_empty(PriorityQueue *q) {
    if (q == NULL || q->list == NULL) {
        return true;
    }
    return false;
}

bool pq_size_is_1(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        return false;
    }

    if ((q->list)->next != NULL) {
        return false;
    }

    return true;
}

bool pq_less_than(ListElement *e1, ListElement *e2) {
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight == e2->tree->weight) {
        if (e1->tree->symbol < e2->tree->symbol) {
            return true;
        }
    }
    return false;
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *newElement = malloc(sizeof(ListElement));
    newElement->tree = tree;
    newElement->next = NULL;

    if (pq_is_empty(q)) {
        newElement->next = q->list;
        q->list = newElement;
    } else if (pq_less_than(newElement, q->list)) {
        newElement->next = q->list;
        q->list = newElement;
    } else {
        ListElement *current = q->list;
        while (current->next != NULL && !pq_less_than(newElement, current->next)) {
            current = current->next;
        }

        newElement->next = current->next;
        current->next = newElement;
    }
}

Node *dequeue(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        exit(1);
    }
    Node *temp = q->list->tree;
    ListElement *f = q->list;
    q->list = q->list->next;

    free(f);
    return temp;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {

            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree);
        e = e->next;
    }
    printf("=============================================\n");
}
