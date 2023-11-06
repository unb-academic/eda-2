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
#include <string.h>

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

bool graph_floyd_warshall(int N, int G[N][N])
{
    int dist[N][N];
    memset(dist, 0, sizeof(dist));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dist[i][j] = G[i][j];

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            if (dist[i][k] != 0)
                for (int j = 0; j < N; j++)
                    if (dist[k][j] == 1)
                        dist[i][j] = 1;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (dist[i][j] == 0)
                return false;

    return true;
}

int main()
{
    while (true)
    {
        int N, M;
        scanf("%d %d", &N, &M);

        if (N == 0 && M == 0)
            break;

        int G[N][N];
        memset(G, 0, sizeof(G));


        for (int i = 0; i < M; i++)
        {
            int V, W, P;
            scanf("%d %d %d", &V, &W, &P);

            if (P == 1)
                G[V - 1][W - 1] = 1;
            else
            {
                G[V - 1][W - 1] = 1;
                G[W - 1][V - 1] = 1;
            }
        }

        if (graph_floyd_warshall(N, G))
            printf("1\n");
        else
            printf("0\n");
    }

    return 0;
}
