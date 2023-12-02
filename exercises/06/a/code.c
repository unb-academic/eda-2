/*
 * MIT License
 *
 * Copyright (c) 2023 UnB
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

typedef struct {
    int count;
    bool visited;
    node_t *first;
} head_t;

typedef struct {
    int size;
    int count;
    head_t *adj;
} graph_t;

graph_t *graph_create(int V) {
    graph_t *G = malloc(sizeof(graph_t));
    G->size = V;
    G->count = 0;
    G->adj = calloc(V, sizeof(head_t));

    for (int i = 0; i < V; i++) {
        G->adj[i].count = 0;
        G->adj[i].first = NULL;
        G->adj[i].visited = false;
    }

    return G;
}

bool graph_dfs(graph_t *G, int t, int x) {
    G->adj[t].visited = true;
    node_t *node = G->adj[t].first;

    while (node != NULL)
    {
        if (node->value == x)
            return true;

        if (!G->adj[node->value].visited)
            if (graph_dfs(G, node->value, x))
                return true;

        node = node->next;
    }

    return false;
}

void graph_insert(graph_t *G, int v, int w) {
    node_t *node = malloc(sizeof(node_t));
    node->value = w;
    node->next = G->adj[v].first;
    G->adj[v].first = node;
    G->adj[v].count++;
}

void graph_reset_visited(graph_t *G) {
    for (int i = 0; i < G->size; i++)
        G->adj[i].visited = false;
}

void graph_print(graph_t *G) {
    for (int i = 0; i < G->size; i++) {
        printf("%d: ", i);

        node_t *node = G->adj[i].first;
        while (node != NULL)
        {
            printf("%d ", node->value);
            node = node->next;
        }

        printf("\n");
    }
}

int main() {
    int V;
    scanf("%d", &V);

    graph_t *G = graph_create(V + 1);
    int v = 1, w = 1, d = 1;

    while (true) {
        scanf("%d %d %d", &v, &w, &d);

        if (v == 0 && w == 0 && d == 0)
            break;

        if (d == 1)
            graph_insert(G, v, w);
        else if (d == 2) {
            graph_insert(G, v, w);
            graph_insert(G, w, v);
        }
    }

    int t, x;

    while (scanf("%d %d", &t, &x) != EOF) {
        if (t == x) {
            printf("Ida e Volta\n");
            continue;
        }

        graph_reset_visited(G);
        bool incoming = graph_dfs(G, t, x);
        graph_reset_visited(G);
        bool outgoing = graph_dfs(G, x, t);

        if (incoming && outgoing)
            printf("Ida e Volta\n");
        else if (incoming)
            printf("Apenas Ida\n");
        else if (outgoing)
            printf("Apenas Volta\n");
        else
            printf("Impossibru\n");
    }

    return 0;
}
