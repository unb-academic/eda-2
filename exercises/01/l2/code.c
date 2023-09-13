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

typedef struct celula
{
    int dado;
    struct celula *prox;
} celula;

void print_celula(celula *node)
{
    while (true)
    {
        if (node == NULL)
        {
            printf("NULL");
            break;
        }
        else
            printf("%d", node->dado);

        printf(" -> ");
        node = node->prox;
    }
    printf("\n");
}

void mescla_listas(celula *l1, celula *l2, celula *l3)
{
    l1 = l1->prox;
    l2 = l2->prox;

    while (true)
    {
        if (l1 == NULL && l2 == NULL)
            break;
        else if (l1 == NULL)
        {
            l3->prox = l2;
            break;
        }
        else if (l2 == NULL)
        {
            l3->prox = l1;
            break;
        }

        if (l1->dado < l2->dado)
        {
            l3->prox = l1;
            l1 = l1->prox;
        }
        else
        {
            l3->prox = l2;
            l2 = l2->prox;
        }

        l3 = l3->prox;
    }
}

void mescla_listas(celula *l1, celula *l2, celula *l3)
{
    // Some base cases
    if (l1 == NULL && l2 == NULL)
        return;
    else if (l1 == NULL)
    {
        l3->prox = l2;
        return;
    }
    else if (l2 == NULL)
    {
        l3->prox = l1;
        return;
    }

    celula *aux;

    if (l1->dado < l2->dado)
    {
        aux = l1->prox;
        l3->prox = l1;
        l1->prox = NULL;
        mescla_listas(aux, l2, l3->prox);
    }
    else
    {
        aux = l2->prox;
        l3->prox = l2;
        l2->prox = NULL;
        mescla_listas(l1, aux, l3->prox);
    }
}

void insert_iterative(celula *node, celula *new)
{
    while (node->prox != NULL)
        node = node->prox;

    new->prox = NULL;
    node->prox = new;
}

celula *celula_new(int data)
{
    celula *node = malloc(sizeof(celula));
    node->dado = data;
    node->prox = NULL;
    return node;
}

int main()
{
    celula *l1 = celula_new(0);
    insert_iterative(l1, celula_new(1));
    insert_iterative(l1, celula_new(7));
    insert_iterative(l1, celula_new(9));
    insert_iterative(l1, celula_new(10));

    celula *l2 = celula_new(0);
    insert_iterative(l2, celula_new(2));
    insert_iterative(l2, celula_new(3));
    insert_iterative(l2, celula_new(8));

    celula *l3 = celula_new(0);

    mescla_listas(l1, l2, l3);

    print_celula(l1);
    print_celula(l2);
    print_celula(l3);
}
