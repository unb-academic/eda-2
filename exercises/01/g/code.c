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

typedef struct _node
{
    item value;
    struct _node *next;
} node;

typedef struct _queue
{
    struct _node *front;
    struct _node *rear;
    int size;
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
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

stack *stack_new()
{
    stack *s = malloc(sizeof(stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

void queue_enqueue(queue *q, item value)
{
    node *n = node_new(value);
    if (q->rear == NULL)
    {
        q->front = n;
        q->rear = n;
    }
    else
    {
        q->rear->next = n;
        q->rear = n;
    }
    q->size++;
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
    node *n = q->front;

    q->front = n->next;
    q->size--;

    item value = n->value;
    free(n);

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
    node *n = q->front;

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

        queue_enqueue(q, N);
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
