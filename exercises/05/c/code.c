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
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node
{
    int value;
    struct node *next;
} node_t;

typedef struct head
{
    int count;
    bool visited;
    node_t *first;
} head_t;

typedef struct
{
    int size;
    int count;
    head_t *adj;
} graph_t;

typedef struct {
    int size;
    int min;
    bool has_j;
} component_t;

graph_t *graph_create(int V)
{
    graph_t *G = malloc(sizeof(graph_t));
    G->size = V;
    G->count = 0;
    G->adj = calloc(V, sizeof(head_t));

    for (int i = 0; i < V; i++)
    {
        G->adj[i].count = 0;
        G->adj[i].first = NULL;
    }

    return G;
}

void graph_insert(graph_t *G, int v, int w)
{
    node_t *node = malloc(sizeof(node_t));
    node->value = w;
    node->next = G->adj[v].first;
    G->adj[v].first = node;
    G->adj[v].count++;
}

void graph_print(graph_t *G)
{
    for (int i = 0; i < G->size; i++)
    {
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

void graph_dfs(graph_t *G, int V, int J, component_t *component)
{
    if (G->adj[V].visited)
        return;

    G->adj[V].visited = true;
    node_t *node = G->adj[V].first;

    component->size++;

    if (V == J)
        component->has_j = true;

    if (V < component->min)
        component->min = V;

    while (node != NULL)
    {
        if (!G->adj[node->value].visited)
            graph_dfs(G, node->value, J, component);

        node = node->next;
    }
}

int main()
{
    int V, J, A, B;
    scanf("%d %d", &V, &J);

    graph_t *G = graph_create(V);

    component_t *best_component = malloc(sizeof(component_t));
    best_component->size = 0;
    best_component->min = INT_MAX;
    best_component->has_j = false;

    component_t *j_component = malloc(sizeof(component_t));
    j_component->size = 0;
    j_component->min = INT_MAX;
    j_component->has_j = false;

    while (scanf("%d %d", &A, &B) != EOF) {
        graph_insert(G, A, B);
        graph_insert(G, B, A);
    }

    for (int i = 0; i < V; i++)
    {
        if (G->adj[i].visited)
            continue;

        component_t *component = malloc(sizeof(component_t));
        component->size = 0;
        component->min = INT_MAX;
        component->has_j = false;

        graph_dfs(G, i, J, component);

        if (component->has_j)
        {
            j_component->size = component->size;
            j_component->min = component->min;
            j_component->has_j = component->has_j;
        }

        if (component->size > best_component->size)
        {
            best_component->size = component->size;
            best_component->min = component->min;
            best_component->has_j = component->has_j;
        }
        else if (component->size == best_component->size && component->min < best_component->min)
        {
            best_component->size = component->size;
            best_component->min = component->min;
            best_component->has_j = component->has_j;
        }
    }

    if (best_component->size == 1)
        printf("Fique em casa\n");
    else if (best_component->size == j_component->size)
        printf("Bora pra estrada\n");
    else
        printf("Vamos para %d\n", best_component->min);

    return 0;
}
