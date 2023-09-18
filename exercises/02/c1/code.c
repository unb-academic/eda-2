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

#define MAX_PRESIDENTS 100
#define MAX_SENATORS 1000
#define MAX_FEDERAL_DEPUTIES 10000
#define MAX_STATE_DEPUTIES 100000

typedef struct candidate
{
    int id;
    int votes;
} candidate;

void merge(candidate votes[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    candidate left_votes[n1], right_votes[n2];

    for (i = 0; i < n1; i++)
        left_votes[i] = votes[left + i];
    for (j = 0; j < n2; j++)
        right_votes[j] = votes[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (left_votes[i].votes < right_votes[j].votes)
        {
            votes[k] = left_votes[i];
            i++;
        }
        else if (left_votes[i].votes > right_votes[j].votes)
        {
            votes[k] = right_votes[j];
            j++;
        }
        else
        {
            if (left_votes[i].id < right_votes[j].id)
            {
                votes[k] = left_votes[i];
                i++;
            }
            else
            {
                votes[k] = right_votes[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1)
    {
        votes[k] = left_votes[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        votes[k] = right_votes[j];
        j++;
        k++;
    }
}

void merge_sort(candidate votes[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        merge_sort(votes, left, middle);
        merge_sort(votes, middle + 1, right);

        merge(votes, left, middle, right);
    }
}

int main()
{
    // This problem seems to be same as the previous one...
    // I don't know why they are different problems.

    unsigned int S, F, E;
    scanf("%d %d %d", &S, &F, &E);

    int C, valid_votes = 0, invalid_votes = 0;
    // Candidates
    candidate presidents[MAX_PRESIDENTS] = {0};
    candidate senators[MAX_SENATORS] = {0};
    candidate federal_deputies[MAX_FEDERAL_DEPUTIES] = {0};
    candidate state_deputies[MAX_STATE_DEPUTIES] = {0};
    // We need to keep track of the total number of votes for the presidents
    // because we need to check if the most voted candidate has more than 51%.
    int president_votes = 0;

    while (scanf("%d", &C) != EOF)
    {
        if (C < 0)
        {
            invalid_votes++;
            continue;
        }

        if (C < MAX_PRESIDENTS)
        {
            presidents[C].id = C;
            presidents[C].votes++;
            president_votes++;
        }
        else if (C < MAX_SENATORS)
        {
            senators[C].id = C;
            senators[C].votes++;
        }
        else if (C < MAX_FEDERAL_DEPUTIES)
        {
            federal_deputies[C].id = C;
            federal_deputies[C].votes++;
        }
        else if (C < MAX_STATE_DEPUTIES)
        {
            state_deputies[C].id = C;
            state_deputies[C].votes++;
        }

        valid_votes++;
    }

    merge_sort(presidents, 0, MAX_PRESIDENTS - 1);
    merge_sort(senators, 0, MAX_SENATORS - 1);
    merge_sort(federal_deputies, 0, MAX_FEDERAL_DEPUTIES - 1);
    merge_sort(state_deputies, 0, MAX_STATE_DEPUTIES - 1);

    printf("%d %d\n", valid_votes, invalid_votes);

    if ((double) (presidents[MAX_PRESIDENTS - 1].votes) / president_votes >= 0.51)
        printf("%d\n", presidents[MAX_PRESIDENTS - 1].id);
    else
        printf("Segundo turno\n");

    for (int i = 0; i < S; ++i)
    {
        // We do this check to avoid a presentation error in the judge
        // since the last number of the output must not have a space after it.
        // If we are not in the last iteration, we print a space after the number.
        if (i != S - 1)
            printf("%d ", senators[MAX_SENATORS - i - 1].id);
        else
            printf("%d\n", senators[MAX_SENATORS - i - 1].id);
    }

    for (int i = 0; i < F; ++i)
    {
        if (i != F - 1)
            printf("%d ", federal_deputies[MAX_FEDERAL_DEPUTIES - i - 1].id);
        else
            printf("%d\n", federal_deputies[MAX_FEDERAL_DEPUTIES - i - 1].id);
    }

    for (int i = 0; i < E; ++i)
    {
        if (i != E - 1)
            printf("%d ", state_deputies[MAX_STATE_DEPUTIES - i - 1].id);
        else
            printf("%d\n", state_deputies[MAX_STATE_DEPUTIES - i - 1].id);
    }

    return 0;
}
