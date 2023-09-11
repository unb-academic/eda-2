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

#define MAX 100001

typedef struct _element
{
    char character;
    int amount;
    int index;
} element;

element *new_element(char character, int amount, int index)
{
    element *e = malloc(sizeof(element));
    e->character = character;
    e->amount = amount;
    e->index = index;
    return e;
}

int compare_elements(const void *a, const void *b)
{
    element *e1 = *(element **)a;
    element *e2 = *(element **)b;

    if (e1->amount == e2->amount)
        return e2->index - e1->index;

    return e1->amount - e2->amount;
}

int main()
{
    char string[MAX], current_char;
    int amount = 0, at = 0, index = 0;
    element *elements[MAX];

    scanf("%s", string);
    current_char = string[0];

    for (int i = 0; string[i] != '\0'; ++i)
    {
        if (string[i] != current_char)
        {
            elements[index] = new_element(current_char, amount, at);
            current_char = string[i];
            amount = 1;
            at = i;
            index++;
            continue;
        }

        amount++;
    }

    elements[index] = new_element(current_char, amount, at);

    // I would use mergesort, but for some reason it is not working.
    // I am probably doing something wrong, but I don't know what.
    qsort(elements, index + 1, sizeof(element *), compare_elements);

    for (int i = index; i > -1; --i)
        printf("%d %c %d\n", elements[i]->amount, elements[i]->character, elements[i]->index);

    return 0;
}
