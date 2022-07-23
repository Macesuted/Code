/**
 * @file interact.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "interact.h"
#include <bits/stdc++.h>
using namespace std;

#define maxn 105

bool queryP(int x, int y) { return query(vector<int>(1, x), vector<int>(1, y)); }
bool queryC(int xl, int xr, int y) {
    vector<int> r, c;
    for (int i = xl; i <= xr; i++) r.push_back(i), c.push_back(y);
    return query(r, c);
}
void checkC(int y, int n) {
    int last = 0;
    for (int i = 1; i <= n + 1; i++) {
        if (!queryP(i, y)) continue;
        if (last) return double_one(last, i, y);
        last = i;
    }
    return inconsistency();
}
void checkR(int x, int n) {
    for (int i = 1; i <= n; i++)
        if (queryP(x, i)) checkC(i, n);
    return all_zero(x);
}

bool v[maxn], vo[maxn];

void work(int n) {
    set<int> S;
    int l = 1, r = n + 1;
    for (int i = 1; i <= n; i++)
        if (v[i] = queryC(l, r, i)) S.insert(i);
    while (!S.empty()) {
        if ((int)S.size() >= r - l + 1) inconsistency();
        int m = (l + r) / 2, cntu = 0, cntd = 0;
        for (auto i : S) vo[i] = queryC(l, m, i);
        for (auto i : S) {
            if (!vo[i]) cntu++;
            if (!(v[i] ^ vo[i])) cntd++;
        }
        if (m - l + 1 > (int)S.size() - cntu) {
            for (auto i : S) v[i] = vo[i];
            r = m;
        } else {
            for (auto i : S) v[i] = v[i] ^ vo[i];
            l = m + 1;
        }
        for (auto i = S.begin(); i != S.end();)
            if (v[*i])
                i++;
            else
                i = S.erase(i);
    }
    assert(l <= r);
    return checkR(l, n);
}