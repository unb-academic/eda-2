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

#define MAX 9999

typedef int item;

typedef struct _node
{
    item value;
    struct _node *next;
} node;

typedef struct _queue
{
    item *array;
    int size;
    int size_multiplier;
} queue;

typedef struct _stack
{
    struct _node *top;
    int size;
} stack;

node *node_new(item value)
{
    node *n = malloc(sizeof(node));
    n->value = value;
    n->next = NULL;
    return n;
}

queue *queue_new()
{
    queue *q = malloc(sizeof(queue));
    q->size_multiplier = 1;
    q->array = malloc(sizeof(item) * MAX * q->size_multiplier);
    q->size = 0;
    return q;
    // queue *q = malloc(sizeof(queue));
    // q->front = NULL;
    // q->rear = NULL;
    // q->size = 0;
    // return q;
}

stack *stack_new()
{
    stack *s = malloc(sizeof(stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

int queue_enqueue(queue *q, item value)
{
    int *ptr;

    if (q->size == MAX * q->size_multiplier)
    {
        q->size_multiplier++;
        ptr = realloc(q->array, sizeof(item) * MAX * q->size_multiplier);

        if (ptr == NULL)
            // We could not realloc, return 1 to indicate failure.
            return 1;

        q->array = ptr;
    }

    q->array[q->size] = value;
    q->size++;

    return 0;

    // if (q->size == MAX)
    //     ptr = realloc(q->array, q->size + MAX);

    // if (ptr == NULL)
    //     return 1;
    // else
    //     q->array = ptr;

    // return 0;
    // node *n = node_new(value);
    // if (q->rear == NULL)
    // {
    //     q->front = n;
    //     q->rear = n;
    // }
    // else
    // {
    //     q->rear->next = n;
    //     q->rear = n;
    // }
    // q->size++;
}

void stack_push(stack *s, item value)
{
    node *n = node_new(value);

    n->next = s->top;
    s->top = n;
    s->size++;
}

item queue_dequeue(queue *q)
{
    item value = q->array[0];

    for (int i = 0; i < q->size; i++)
        q->array[i] = q->array[i + 1];

    q->size--;
    return value;
}

item stack_pop(stack *s)
{
    node *n = s->top;

    s->top = n->next;
    s->size--;

    item value = n->value;
    free(n);

    return value;
}

void queue_print(queue *q)
{
    printf("[");
    for (int i = 0; i < q->size; ++i)
    {
        printf("%d", q->array[i]);

        if (i < q->size - 1)
            printf(", ");
    }
    printf("]\n");
}

void stack_print(stack *q)
{
    node *n = q->top;

    printf("[");
    while (n)
    {
        printf("%d", n->value);
        n = n->next;

        if (n)
            printf(", ");
    }
    printf("]\n");
}

int main()
{
    int N, L, total = 0;
    queue *q = queue_new();
    stack *s = stack_new();

    while (true)
    {
        scanf("%d", &N);

        if (N == 0)
            break;

        int res = queue_enqueue(q, N);

        if (res == 1)
            return 1;
    }

    scanf("%d", &L);

    while (q->size != 0)
    {
        int n = queue_dequeue(q);

        if ((total + n) > L)
        {
            total = 0;
            stack_push(s, n);
        }
        else
            total += n;
    }

    while (s->size != 0)
        printf("%d\n", stack_pop(s));

    return 0;
}
