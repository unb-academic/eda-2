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
#include <string.h>

#define MAX 1001

typedef struct node
{
    int value;
    int count;
} node;

void merge(node nodes[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    node left_nodes[n1], right_nodes[n2];

    for (i = 0; i < n1; i++)
        left_nodes[i] = nodes[left + i];
    for (j = 0; j < n2; j++)
        right_nodes[j] = nodes[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (left_nodes[i].count < right_nodes[j].count)
        {
            nodes[k] = left_nodes[i];
            i++;
        }
        else if (left_nodes[i].count > right_nodes[j].count)
        {
            nodes[k] = right_nodes[j];
            j++;
        }
        else
        {
            if (left_nodes[i].value < right_nodes[j].value)
            {
                nodes[k] = left_nodes[i];
                i++;
            }
            else
            {
                nodes[k] = right_nodes[j];
                j++;
            }
        }

        k++;
    }

    while (i < n1)
    {
        nodes[k] = left_nodes[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        nodes[k] = right_nodes[j];
        j++;
        k++;
    }
}

void merge_sort(node nodes[], int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;

        merge_sort(nodes, left, middle);
        merge_sort(nodes, middle + 1, right);

        merge(nodes, left, middle, right);
    }
}

int main()
{
    char string[MAX];
    bool first = true;

    while (scanf("%s", string) != EOF)
    {
        if (first)
            first = false;
        else
            printf("\n");

        node nodes[128];
        memset(nodes, 0, sizeof(nodes));

        for (int i = 0; i < strlen(string); i++)
        {
            nodes[string[i]].value = string[i];
            nodes[string[i]].count++;
        }

        merge_sort(nodes, 0, 127);

        for (int i = 0; i < 128; i++)
            if (nodes[i].count > 0)
                printf("%d %d\n", nodes[i].value, nodes[i].count);
    }

    return 0;
}
