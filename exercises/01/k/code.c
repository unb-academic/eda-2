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

bool binary_search(int vector[], int left, int right, int element)
{
    if (left > right)
        return false;

    int middle = (left + right) / 2;

    if (vector[middle] == element)
        return true;

    if (vector[middle] > element)
        return binary_search(vector, left, middle - 1, element);

    return binary_search(vector, middle + 1, right, element);
}

int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

int main()
{
    int N, X;
    scanf("%d", &N);

    int P[N];

    for (int i = 0; i < N; ++i)
        scanf("%d", &P[i]);

    qsort(P, N, sizeof(int), compare);

    while (scanf("%d", &X) != EOF)
    {
        if (binary_search(P, 0, N - 1, X))
            printf("sim\n");
        else
            printf("nao\n");
    }

    return 0;
}
