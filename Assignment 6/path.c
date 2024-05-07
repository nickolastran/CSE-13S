#include "path.h"

#include "graph.h"
#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p == NULL) {
        return NULL;
    }
    p->total_weight = 0;
    p->vertices = stack_create(capacity);

    return p;
}

void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        Path *p = *pp;
        stack_free(&p->vertices);
        free(p);
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_size(p->vertices) >= 1) {
        uint32_t prev_vertex = 0;
        stack_peek(p->vertices, &prev_vertex);
        p->total_weight += graph_get_weight(g, prev_vertex, val);
    }
    stack_push(p->vertices, val);
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex;
    stack_pop(p->vertices, &removed_vertex);

    if (path_vertices(p) >= 1) {
        uint32_t new_top_vertex = 0;
        stack_peek(p->vertices, &new_top_vertex);
        uint32_t prev_vertex = removed_vertex;
        p->total_weight -= graph_get_weight(g, new_top_vertex, prev_vertex);
    } else {
        p->total_weight = 0;
    }
    return removed_vertex;
}

void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    if (p == NULL || f == NULL || g == NULL)
        return;

    Stack *temp = stack_create(stack_size(p->vertices));
    while (!stack_empty(p->vertices)) {
        uint32_t vertex;
        stack_pop(p->vertices, &vertex);
        stack_push(temp, vertex);
    }

    while (!stack_empty(temp)) {
        uint32_t vertex;
        stack_pop(temp, &vertex);
        fprintf(f, "%s\n", graph_get_vertex_name(g, vertex));
        stack_push(p->vertices, vertex);
    }
    stack_free(&temp);
}
