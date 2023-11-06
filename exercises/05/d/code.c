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

typedef struct node {
    int value;
    struct node *next;
} node_t;

typedef struct head {
    int count;
    char value[31];
    bool visited;
    node_t *first;
} head_t;

typedef struct graph {
    int size;
    int count;
    head_t *adj;
} graph_t;

typedef struct {
    char key[31];
    int value;
} hashtable_item_t;

typedef struct {
    hashtable_item_t *items;
    int size;
} hashtable_t;

int hash(char *name, int size)
{
    long long h, a = 31415, b = 27183;

    for (h = 0; *name != '\0'; name++)
    {
        a = a * b % (size - 1);
        h = (a * h + *name) % size;
    }

    return h < 0 ? 0 : h;
}

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

hashtable_t *ht_create(int size)
{
    hashtable_t *table = malloc(sizeof(hashtable_t));
    table->size = size;
    table->items = calloc(size, sizeof(hashtable_item_t));

    for (int i = 0; i < size; i++)
        table->items[i].value = -1;

    return table;
}

int ht_search(hashtable_t *T, char *name)
{
    int h = hash(name, T->size);

    while (T->items[h].value != -1)
    {
        if (strcmp(T->items[h].key, name) == 0)
            return T->items[h].value;

        h = (h + 1) % T->size;
    }

    return -1;
}

void ht_insert(hashtable_t *T, char *name, int index)
{
    int h = hash(name, T->size);

    while (T->items[h].value != -1)
        h = (h + 1) % T->size;

    T->items[h].value = index;
    strcpy(T->items[h].key, name);
}

void ht_print(hashtable_t *T)
{
    for (int i = 0; i < T->size; i++)
        if (T->items[i].value != -1)
            printf("%d: %d\n", i, T->items[i].value);
}

void graph_insert(graph_t *G, hashtable_t *T, char *from, char *to) {
    if (ht_search(T, from) == -1)
    {
        strcpy(G->adj[G->count].value, from);
        ht_insert(T, from, G->count);
        G->count++;
    }

    if (ht_search(T, to) == -1)
    {
        strcpy(G->adj[G->count].value, to);
        ht_insert(T, to, G->count);
        G->count++;
    }

    int from_index = ht_search(T, from);
    int to_index = ht_search(T, to);

    node_t *node;

    node = malloc(sizeof(node_t));
    node->value = to_index;
    node->next = G->adj[from_index].first;
    G->adj[from_index].first = node;
    G->adj[from_index].count++;

    node = malloc(sizeof(node_t));
    node->value = from_index;
    node->next = G->adj[to_index].first;
    G->adj[to_index].first = node;
    G->adj[to_index].count++;
}

void graph_dfs(graph_t *G, int v, int *count)
{
    if (G->adj[v].visited)
        return;

    G->adj[v].visited = true;
    node_t *node = G->adj[v].first;

    (*count)++;

    while (node != NULL)
    {
        if (!G->adj[node->value].visited)
            graph_dfs(G, node->value, count);

        node = node->next;
    }
}

void graph_print(graph_t *G) {
    for (int i = 0; i < G->size; i++) {
        if (G->adj[i].count == 0)
            continue;

        printf("%s: ", G->adj[i].value);

        node_t *node = G->adj[i].first;
        while (node != NULL) {
            printf("%s ", G->adj[node->value].value);
            node = node->next;
        }

        printf("\n");
    }
}

int main()
{
    while (true)
    {
        int R, C;
        scanf("%d %d", &R, &C);

        if (R == 0 && C == 0)
            break;

        graph_t *G = graph_create(R);
        hashtable_t *T = ht_create(R + 50);


        for (int i = 0; i < R; i++)
        {
            char name[31];
            scanf("%s", name);
        }

        for (int i = 0; i < C; i++)
        {
            char from[31], to[31];
            scanf("%s %s", to, from);

            graph_insert(G, T, from, to);
        }

        int res = 1;

        for (int i = 0; i < G->size; i++)
        {
            if (G->adj[i].count == 0)
                continue;

            int count = 0;
            graph_dfs(G, i, &count);

            if (count > res)
                res = count;
        }

        printf("%d\n", res);
    }

    return 0;
}
