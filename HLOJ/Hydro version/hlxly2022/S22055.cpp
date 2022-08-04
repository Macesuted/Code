/**
 * @file S22055.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "o.h"
#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

int S[maxn], T[maxn], p[maxn], pcnt, pp;

int query(vector<int> a, vector<int> b) {
    int n = a.size(), m = b.size();
    for (int i = 0; i < n; i++) S[i] = a[i];
    for (int i = 0; i < m; i++) T[i] = b[i];
    return query(S, n, T, m);
}
int query(int a, int b) { return query(vector<int>{a}, vector<int>{b}); }
int query(int a, int b, int c) { return query(vector<int>{a}, vector<int>{b, c}); }

void solve(int task_id, int n, int md, int ans[]) {
    pcnt = 0, pp = -1;
    for (int i = 0; i < n; ++i) ans[i] = 0;
    if (n == 1) {
        ans[0] = 1;
        return;
    }
    if (n == 2) {
        if (md)
            ans[query(0, 1)] = 1;
        else
            ans[0] = ans[1] = 1;
        return;
    }
    if (task_id == 3)
        if (query(0, n - 1))
            for (int i = 0; i < n; i++) p[pcnt++] = i;
        else
            for (int i = n - 1; ~i; i--) p[pcnt++] = i;
    else {
        int a = p[pcnt++] = 0, b = 1;
        for (int i = 2; i < n; i++) {
            int c = i;
            if (query(b, c)) swap(b, c);
            if (query(a, b, c)) p[pcnt++] = b, a = b, b = c;
        }
        if (query(a, b))
            p[pcnt++] = b;
        else
            pp = b;
    }
    int pq = -1;
    ans[p[pcnt - 1]] = 1;
    if (pcnt == 1)
        pq = pp, pp = -1;
    else if (pcnt == 2)
        pq = p[0];
    else if (query(p[pcnt - 1], p[0], p[1])) {
        pq = p[0];
        for (int i = 1; i < pcnt - 1; i++) ans[p[i]] = 1;
    } else if (!query(p[pcnt - 1], p[pcnt - 3], p[pcnt - 2]))
        pq = p[pcnt - 2];
    else {
        int l = 0, r = pcnt - 3;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            (query(p[pcnt - 1], p[mid], p[mid + 1]) ? r : l) = mid;
        }
        for (int i = r + 1; i < pcnt - 1; i++) ans[p[i]] = 1;
        pq = p[r];
    }
    if (~pp) {
        if (query(pp, pq)) swap(pp, pq);
        if (query(p[pcnt - 1], pp, pq))
            ans[pp] = 1;
        else
            pq = pp;
    }
    bool cnt = 0;
    for (int i = 0; i < n; i++) cnt ^= ans[i];
    ans[pq] = cnt ^ md;
    return;
}
