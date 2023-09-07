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

int main()
{
    int N, day = 0;
    scanf("%d", &N);

    while (true)
    {
        int code = 10000000, note = 0;
        int temp_code, temp_note;

        for (int i = 0; i < N; ++i)
        {
            scanf("%d %d", &temp_code, &temp_note);

            if (temp_note < note)
                continue;

            if (temp_note == note && temp_code > code)
                continue;

            note = temp_note;
            code = temp_code;
        }

        printf("Dia %d\n", ++day);
        printf("%d\n", code);

        if (scanf("%d", &N) == EOF)
            break;
        else
            printf("\n");

        code = 10000000;
        note = 0;
    }

    return 0;
}
