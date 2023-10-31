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

typedef struct
{
    int *items;
    int size;
    int capacity;
} priority_queue;

priority_queue *pq_new(int capacity)
{
    priority_queue *pq = malloc(sizeof(priority_queue));
    pq->items = malloc(sizeof(int) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void pq_fix_up(priority_queue *pq, int k)
{
    int v = pq->items[k];

    while (k > 1 && pq->items[k / 2] > v)
    {
        pq->items[k] = pq->items[k / 2];
        k /= 2;
    }

    pq->items[k] = v;
}

void pq_fix_down(priority_queue *pq, int k)
{
    int j, v = pq->items[k];

    while (2 * k <= pq->size)
    {
        j = 2 * k;

        if (j < pq->size && pq->items[j] > pq->items[j + 1])
            j++;

        if (v <= pq->items[j])
            break;

        pq->items[k] = pq->items[j];
        k = j;
    }

    pq->items[k] = v;
}

int pq_find_max(priority_queue *pq)
{
    if (pq->size == 0)
        return -1;

    int index = 1;

    for (int i = 2; i <= pq->size; i++)
        if (pq->items[i] > pq->items[index])
            index = i;

    return index;
}

void pq_insert(priority_queue *pq, int v)
{
    if (pq->size == pq->capacity)
    {
        // If the queue is full, we have two scenarios:
        //   1. The new element is greater than the maximum element in the
        //       queue. In this case, we can just ignore the new element.
        //   2. The new element is less than the maximum element in the queue.
        //       In this case, we can remove the maximum element and insert
        //       the new one, and then fix the queue.
        int max_index = pq_find_max(pq);

        if (v > pq->items[max_index])
            return;

        pq->items[max_index] = v;
        pq_fix_down(pq, 1);
        pq_fix_up(pq, max_index);
        return;
    }

    pq->items[++pq->size] = v;
    pq_fix_up(pq, pq->size);
}

void pq_remove_max(priority_queue *pq)
{
    if (pq->size == 0)
        return;

    swap(&pq->items[1], &pq->items[pq->size--]);
    pq_fix_down(pq, 1);
}

priority_queue *pq_copy(priority_queue *pq)
{
    priority_queue *copy = pq_new(pq->capacity);

    for (int i = 1; i <= pq->size; i++)
        copy->items[i] = pq->items[i];

    copy->size = pq->size;
    copy->capacity = pq->capacity;

    return copy;
}

void pq_get_n(priority_queue *pq, int n)
{
    priority_queue *copy = pq_copy(pq);

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
            printf("%d", copy->items[1]);
        else
            printf("%d ", copy->items[1]);

        pq_remove_max(copy);
    }
    printf("\n");

    free(copy->items);
    free(copy);
}

void pq_print(priority_queue *pq)
{
    for (int i = 1; i <= pq->size; i++)
        printf("(%d, %d) ", i, pq->items[i]);
    printf("\n");
}

int main()
{
    int cmd, obj;
    priority_queue *pq = pq_new(101);

    while (scanf("%d %d", &cmd, &obj) != EOF)
    {
        if (cmd == 1)
            pq_insert(pq, obj);
        else if (cmd == 2)
            pq_get_n(pq, obj);
    }

    return 0;
}
