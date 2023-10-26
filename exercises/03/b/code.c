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

typedef int item;

static item qp[100005];
static item pq[100005];
static item N;

int *vector;

#define greater(a, b) (vector[a] > vector[b])

void pq_exchange(int i, int j) {
    int t = qp[i];
    qp[i] = qp[j];
    qp[j] = t;

    pq[qp[i]] = i;
    pq[qp[j]] = j;
}

void pq_init() {
    N = 0;
}

int pq_spy() {
    return vector[pq[1]];
}

void pq_fix_up(item *pq, int k) {
    while (k > 1 && greater(pq[k / 2], pq[k])) {
        pq_exchange(pq[k], pq[k / 2]);
        k /= 2;
    }
}

void pq_fix_down(item *pq, int k, int N) {
    int j;

    while (2 * k <= N) {
        j = 2 * k;

        if (j < N && greater(pq[j], pq[j + 1]))
            j++;

        if (!greater(pq[k], pq[j]))
            break;

        pq_exchange(pq[k], pq[j]);
        k = j;
    }
}

void pq_change(int k) {
    pq_fix_up(pq, qp[k]);
    pq_fix_down(pq, qp[k], N);
}

int pq_empty() {
    return N == 0;
}

void pq_insert(item k) {
    qp[k] = ++N;
    pq[N] = k;
    pq_fix_up(pq, N);
}

item pq_delete_min() {
    pq_exchange(pq[1], pq[N]);
    pq_fix_down(pq, 1, N - 1);
    return pq[N--];
}

void solve(int n, int k, int *v) {
    int older = 0;
    int next = k;
    vector = v;
    pq_init();

    for (int i = 0; i < k; i++)
        pq_insert(i);

    while (next <= n) {
        if (next == n)
            printf("%d", pq_spy());
        else
            printf("%d ", pq_spy());

        v[older] = 0;
        pq_change(older);
        pq_delete_min();
        older++;
        pq_insert(next);
        next++;
    }
    printf("\n");
}

int main() {
    int v[100005];
    int n, k;

    while (scanf("%d %d", &n, &k) == 2 && n != 0 && k != 0) {
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);

        solve(n, k, v);
    }

    return 0;
}
