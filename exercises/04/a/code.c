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

#define MAX 10000000
#define less(a, b) (((a.quality) == (b.quality)) ? ((a.id) < (b.id)) : ((a.quality) < (b.quality)))
#define less_id(a, b) ((a.id) < (b.id))
#define exch(a, b) { seed t = a; a = b; b = t; }
#define cmpexch(a, b) { if (less_id(b, a)) exch(a, b); }

typedef struct {
    long long id;
    int quality;
} seed;

int partition(seed *vector, int l, int r)
{
    int i = l - 1, j = r;
    seed v = vector[r];

    for (;;)
    {
        while (++i, less(vector[i], v));
        while (--j, less(v, vector[j]))
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(vector[i], vector[j]);
    }

    exch(vector[i], vector[r])
    return i;
}

void quickselect(seed *vector, int l, int r, int k)
{
    if (r <= l)
        return;

    int i = partition(vector, l, r);

    if (i > k)
        quickselect(vector, l, i - 1, k);
    if (i < k)
        quickselect(vector, i + 1, r, k);
}

void seed_print(seed *vector, int size)
{
    for (int i = 0; i < size; i++)
        printf("%lld %d\n", vector[i].id, vector[i].quality);
}

void merge(seed *vector, int l, int m, int r)
{
    seed *aux = malloc((r - l + 1) * sizeof(seed));

    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r)
        if (less_id(vector[i], vector[j]))
            aux[k++] = vector[i++];
        else
            aux[k++] = vector[j++];

    while (i <= m)
        aux[k++] = vector[i++];
    while (j <= r)
        aux[k++] = vector[j++];

    k = 0;
    for (int i = l; i <= r; i++)
        vector[i] = aux[k++];

    free(aux);
}

// `mergesort` is already defined in `stdlib.h`.
void mergesort_(seed *vector, int l, int r)
{
    if (l >= r)
        return;

    int m = (l + r) / 2;

    mergesort_(vector, l, m);
    mergesort_(vector, m + 1, r);
    merge(vector, l, m, r);
}

int main()
{
    int N, size = 0;
    scanf("%d", &N);

    seed *array = malloc(MAX * sizeof(seed));

    long long A;
    int B;

    while (scanf("%lld %d", &A, &B) != EOF)
        array[size++] = (seed) { A, B };

    quickselect(array, 0, size - 1, N - 1);
    mergesort_(array, 0, N - 1);

    seed_print(array, N);

    return 0;
}
