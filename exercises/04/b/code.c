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

#define less(a, b) ((a) < (b))
#define exch(a, b) { int t = a; a = b; b = t; }
#define cmpexch(a, b) { if (less(b, a)) exch(a, b); }

int partition(int *vector, int l, int r)
{
    int i = l - 1, j = r;
    int v = vector[r];

    for (;;)
    {
        while (less(vector[++i], v));
        while (less(v, vector[--j]))
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(vector[i], vector[j]);
    }

    exch(vector[i], vector[r])
    return i;
}

void quickselect(int *vector, int l, int r, int k)
{
    if (r <= l)
        return;

    int i = partition(vector, l, r);

    if (i > k)
        quickselect(vector, l, i - 1, k);
    if (i < k)
        quickselect(vector, i + 1, r, k);
}

void quicksort_m3(int *vector, int l, int r)
{
    if (r <= l)
        return;

    cmpexch(vector[(l + r) / 2], vector[r]);
    cmpexch(vector[l], vector[(l + r) / 2]);
    cmpexch(vector[r], vector[(l + r) / 2]);

    int j = partition(vector, l, r);
    quicksort_m3(vector, l, j - 1);
    quicksort_m3(vector, j + 1, r);
}

int main()
{
    int N, P, X;
    scanf("%d %d %d", &N, &P, &X);

    int vector[N];

    for (int i = 0; i < N; i++)
        scanf("%d", &vector[i]);

    int start = X * P;
    int end = start + X;

    if (end > N)
        end = N;

    quickselect(vector, 0, N - 1, start);
    quickselect(vector, start, N - 1, end);
    quicksort_m3(vector, start - 1, end - 1);

    for (int i = start; i < end; i++)
        printf("%d\n", vector[i]);

    return 0;
}
