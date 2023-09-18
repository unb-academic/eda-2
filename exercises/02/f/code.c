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
#include <stdlib.h>
#include <stdbool.h>

#define M 101

char *table[M];

int hash(char *key, int len)
{
    int r = 0;

    for (int i = 0; i < len; ++i)
        r += (key[i] * (i + 1)) % M;

    return (19 * r) % M;
}

int main()
{
    bool flag;
    int T, N, pos, len, count;
    char string[30], cmd, *key;

    scanf("%d", &T);

    while (T--)
    {
        count = 0;

        for (int i = 0; i < N; ++i)
            table[i] = NULL;

        scanf("%d", &N);

        for (int i = 0; i < N; ++i)
        {
            scanf("%s", string);

            key = &string[4];
            cmd = string[0];
            len = strlen(key);

            if (cmd == 'A')
            {
                flag = true;

                for (int j = 0; j < 20; ++j)
                {
                    pos = (hash(key, len) + (j*j) + (23*j)) % M;

                    if (table[pos] != NULL && strcmp(key, table[pos]) == 0)
                    {
                        flag = false;
                        break;
                    }
                }

                if (flag)
                {
                    for (int j = 0; j < 20; ++j)
                    {
                        pos = (hash(key, len) + j*j + 23*j) % M;

                        if (table[pos] == NULL)
                        {
                            table[pos] = malloc(sizeof(char) * (len + 1));
                            strcpy(table[pos], key);
                            count++;
                            break;
                        }
                    }
                }
            }
            else
            {
                for (int j = 0; j < 20; ++j)
                {
                    pos = (hash(key, len) + j*j + 23*j) % M;

                    if (table[pos] != NULL && strcmp(table[pos], key) == 0)
                    {
                        free(table[pos]);
                        table[pos] = NULL;
                        count--;
                        break;
                    }
                }
            }
        }

        printf("%d\n", count);

        for (int j = 0; j < M; ++j)
            if (table[j] != NULL)
                printf("%d:%s\n", j, table[j]);
    }

    return 0;
}
