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

#define MAX 10485760

typedef struct node
{
    unsigned int key;
    char value;
} node;

int hash(unsigned int key)
{
    return key % MAX;
}

void ht_insert(node *table, unsigned int key, char value)
{
    int h = hash(key);

    while (table[h].key != 0)
    {
        if (table[h].key == key)
            return;

        h = (h + 1) % MAX;
    }

    table[h].key = key;
    table[h].value = value;
}

char ht_search(node *table, unsigned int key)
{
    int h = hash(key);

    while (table[h].key != 0)
    {
        if (table[h].key == key)
            return table[h].value;

        h = (h + 1) % MAX;
    }

    return '\0';
}

int main()
{
    unsigned int S, min = 4294967295, max = 0;
    char C;

    node *table = calloc(MAX, sizeof(node));

    while (scanf("%d %c", &S, &C) != EOF)
    {
        ht_insert(table, S, C);

        if (S < min)
            min = S;

        if (S > max)
            max = S;
    }

    for (unsigned int i = min; i <= max + 1; i++)
    {
        char c = ht_search(table, i);

        if (c != '\0')
            printf("%c", c);
    }
    printf("\n");

    return 0;
}
