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
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef char item;

typedef struct _node
{
    item value[200];
    struct _node *next;
} node;

typedef struct _stack
{
    struct _node *top;
    int size;
} stack;

node *node_new(item value[])
{
    node *n = malloc(sizeof(node));
    strcpy(n->value, value);
    n->next = NULL;
    return n;
}

stack *stack_new()
{
    stack *s = malloc(sizeof(stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

void stack_push(stack *s, item value[])
{
    node *n = node_new(value);
    n->next = s->top;
    s->top = n;
    s->size++;
}

void stack_pop(stack *s)
{
    node *n = s->top;

    s->top = n->next;
    s->size--;

    printf("%s\n", n->value);
    free(n);
}

void stack_print(stack *s)
{
    node *n = s->top;

    printf("[");
    while (n)
    {
        printf("'%s'", n->value);
        n = n->next;

        if (n)
            printf(", ");
    }
    printf("]\n");
}

bool stack_is_empty(stack *s)
{
    return s->size == 0;
}

int main()
{
    char token[20], string[200];
    stack *s = stack_new();

    while (scanf("%s", token) != EOF)
    {
        if (strcmp(token, "desfazer") == 0)
            if (stack_is_empty(s))
                printf("NULL\n");
            else
                stack_pop(s);
        else if (strcmp(token, "inserir") == 0)
        {
            scanf(" %4000[^\n]s", string);
            stack_push(s, string);
        }
    }

    return 0;
}
