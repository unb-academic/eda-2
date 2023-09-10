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

typedef int item;

typedef struct _head
{
    struct _node *root;
    int total;
} head;

typedef struct _node
{
    item value;
    struct _node *left;
    struct _node *right;
} node;

head *head_new()
{
    head *h = malloc(sizeof(head));
    h->root = NULL;
    h->total = 0;
    return h;
}

node *node_new(item value)
{
    node *n = malloc(sizeof(node));
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void head_insert(head *h, item value)
{
    node *n = node_new(value);
    if (h->root == NULL)
    {
        h->root = n;
        h->total++;
        return;
    }

    node *current = h->root;

    while (true)
    {
        if (current->value == value)
            return;

        if (value < current->value)
        {
            if (current->left == NULL)
            {
                current->left = n;
                h->total++;
                return;
            }
            current = current->left;
        }
        else
        {
            if (current->right == NULL)
            {
                current->right = n;
                h->total++;
                return;
            }
            current = current->right;
        }
    }
}

int main()
{
    item N, value;
    scanf("%d", &N);

    head *h = head_new();

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &value);
        head_insert(h, value);
    }

    printf("%d\n", h->total);

    return 0;
}
