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

typedef struct node
{
    int value;
    struct node *next;
} node_t;

typedef struct head
{
    int count;
    bool infected;
    node_t *first;
} head_t;

typedef struct graph
{
    int size;
    int count;
    head_t *adj;
} graph_t;

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
        G->adj[i].infected = false;
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

int main()
{
    int N, M, J, A, B;
    scanf("%d %d %d", &N, &M, &J);

    graph_t *G = graph_create(N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A);

        while (A--)
        {
            scanf("%d", &B);
            graph_insert(G, i, B);
        }
    }

    while (M--)
    {
        scanf("%d", &A);

        G->adj[A].infected = true;
        node_t *node = G->adj[A].first;

        while (node != NULL)
        {
            G->adj[node->value].infected = true;
            node = node->next;
        }
    }

    while (J--)
    {
        scanf("%d", &A);

        if (G->adj[A].infected)
            printf("Eu vou estar la\n");
        else
            printf("Nao vou estar la\n");
    }

    return 0;
}
