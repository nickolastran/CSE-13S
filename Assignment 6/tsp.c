#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void DFS(Graph *g, Path *p, Path *result, uint32_t start, uint32_t end) {
    graph_visit_vertex(g, start);
    path_add(p, start, g);
    if (path_vertices(p) == end) {
        if (graph_get_weight(g, start, 0)) {
            path_add(p, 0, g);
            if (path_distance(result) == 0 || path_distance(p) < path_distance(result)) {
                path_copy(result, p);
            }
        }
        path_remove(p, g);
    }

    for (uint32_t i = 0; i < end; i++) {
        if (graph_get_weight(g, start, i)) {
            bool vertex = graph_visited(g, i);
            if (!vertex) {
                DFS(g, p, result, i, end);
            }
        }
    }

    graph_unvisit_vertex(g, start);
    path_remove(p, g);
}

int main(int argc, char **argv) {
    int opt;
    bool dir = false;
    FILE *in = stdin;
    FILE *out = stdout;

    while ((opt = getopt(argc, argv, "do:hi:")) != -1) {
        switch (opt) {
        case 'i': in = fopen(optarg, "r"); break;
        case 'o': out = fopen(optarg, "w"); break;
        case 'd': dir = true; break;
        case 'h':
            fprintf(stdout, "Usage: tsp [options]\n\n");
            fprintf(stdout,
                "-i infile    Specify the input file path containing the cities and edges\n");
            fprintf(stdout,
                "             of the graph. If not specified, the default input should be\n");
            fprintf(stdout, "             set as stdin.\n\n");
            fprintf(stdout,
                "-o outfile   Specify the output file path to print to. If not specified,\n");
            fprintf(stdout, "             the default output should be stdout.\n\n");
            fprintf(stdout, "-d           Specifies the graph to be directed.\n\n");
            fprintf(
                stdout, "-h           Print out a help message describing the purpose of the\n");
            fprintf(stdout,
                "             graph and the command-line options it accepts, exiting the\n");
            fprintf(stdout, "             program afterwards\n");
            return 0;
            break;
        default:
            fprintf(stderr, "tsp: unknown or poorly formatted option -i\n");
            fclose(in);
            fclose(out);
            return 0;
            break;
        }
    }

    uint32_t num_vertices;
    if (fscanf(in, "%u\n", &num_vertices) != 1) {
        fprintf(stderr, "tsp: error reading number of vertices\n");
        fclose(in);
        fclose(out);
        return 0;
    } else {
        fscanf(in, "%u\n", &num_vertices);
    }

    Graph *g = graph_create(num_vertices, dir);

    char name[100];
    for (uint32_t i = 0; i < num_vertices; i++) {
        fgets(name, sizeof(name), in);
        name[strcspn(name, "\n")] = 0;
        graph_add_vertex(g, name, i);
    }

    uint32_t edge;
    uint32_t start;
    uint32_t end;
    uint32_t weight;
    if (fscanf(in, "%u\n", &edge) != 1) {
        fprintf(stderr, "tsp:  must provide number of edges\n");
        fclose(in);
        fclose(out);
        return 0;
    }

    for (uint32_t m = 0; m < edge; m++) {
        if (fscanf(in, "%u %u %u", &start, &end, &weight) != 3) {
            fprintf(stderr, "'tsp:  error reading edge\n");
            return 0;
        } else {
            graph_add_edge(g, start, end, weight);
        }
    }

    Path *p = path_create(num_vertices + 1);
    Path *result = path_create(num_vertices + 1);
    DFS(g, p, result, 0, num_vertices);

    if (path_distance(result)) {
        fprintf(out, "Alissa starts at:\n");
        path_print(result, out, g);
        fprintf(out, "Total Distance: %d\n", path_distance(result));
    } else {
        fprintf(out, "No path found! Alissa is lost!\n");
    }

    path_free(&p);
    path_free(&result);
    graph_free(&g);
    fclose(in);
    fclose(out);
    return 0;
}
