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
#include <stdlib.h>

typedef struct celula
{
    char matricula[10];
    double mediaAtividades;
    double mediaProvas;
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
            printf("{\"%s\", %.1f, %.1f}",
                node->matricula,
                node->mediaAtividades,
                node->mediaProvas);

        printf(" -> ");
        node = node->prox;

    }
    printf("\n");
}

void insert_iterative(celula *node, celula *new)
{
    while (node->prox != NULL)
        node = node->prox;

    new->prox = NULL;
    node->prox = new;
}

void relatorioMediaAtividades(celula *le, celula *l1, celula *l2, double media)
{
    le = le->prox;

    while (true)
    {
        if (le == NULL)
            break;

        celula *aux = le->prox;

        if (le->mediaAtividades <= media)
        {
            l1->prox = le;
            l1 = le;
        }
        else
        {
            l2->prox = le;
            l2 = le;
        }

        le->prox = NULL;
        le = aux;
    }
}

celula *celula_new(char matricula[], double mediaAtividades, double mediaProvas)
{
    celula *node = malloc(sizeof(celula));
    strcpy(node->matricula, matricula);
    node->mediaAtividades = mediaAtividades;
    node->mediaProvas = mediaProvas;
    node->prox = NULL;
    return node;
}

int main()
{
    celula *le = celula_new("", 0.0, 0.0);
    insert_iterative(le, celula_new("140164006", 10.0, 8.0));
    insert_iterative(le, celula_new("160016169", 4.0, 2.0));
    insert_iterative(le, celula_new("170062465", 9.5, 8.5));
    insert_iterative(le, celula_new("190262661", 5.0, 7.0));

    celula *l1 = celula_new("", 0.0, 0.0);
    celula *l2 = celula_new("", 0.0, 0.0);

    relatorioMediaAtividades(le, l1, l2, 6.0);

    printf("resultado final:\n");
    print_celula(le);
    print_celula(l1);
    print_celula(l2);

    return 0;
}
