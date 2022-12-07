/**
 * @file 240.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
#include "aliens.h"
using namespace std;

#define maxn 100005

typedef pair<int, int> pii;
typedef pair<int64_t, int> pli;
typedef pair<int64_t, int64_t> pll;

pii a[maxn];
pli f[maxn];
deque<int> que;

int64_t sqr(int64_t v) { return v * v; }
int64_t A(int i) { return -2 * a[i].first + 2; }
int64_t B(int i) { return f[i - 1].first + sqr(a[i].first - 1) - sqr(max(0, a[i - 1].second - a[i].first + 1)); }
double pos(int i, int j) { return double(B(i) - B(j)) / (A(j) - A(i)); }
int64_t getVal(int i, int64_t v) { return A(i) * v + B(i); }

pli check(int n, int64_t lim) {
    f[0] = {0, 0}, que.clear();
    for (int i = 1; i <= n; i++) {
        while (que.size() > 1 && pos(i, que[0]) < pos(que[0], que[1])) que.pop_front();
        que.push_front(i);
        while (que.size() > 1 && a[i].second > pos(que[(int)que.size() - 1], que[(int)que.size() - 2])) que.pop_back();
        int p = que.back();
        f[i] = {sqr(a[i].second) + getVal(p, a[i].second) + lim, f[p - 1].second + 1};
    }
    return f[n];
}

long long take_photos(int n, int m, int k, vector<int> r, vector<int> c) {
    for (int i = 0; i < n; i++) {
        if (r[i] > c[i]) swap(r[i], c[i]);
        a[i + 1] = {r[i] + 1, c[i] + 1};
    }
    sort(a + 1, a + n + 1, [&](pii x, pii y) { return pii{x.first, -x.second} < pii{y.first, -y.second}; });
    int tn = 0;
    for (int i = 1, my = -1; i <= n; i++)
        if (a[i].second > my) my = a[i].second, a[++tn] = a[i];
    int64_t L = 0, R = 1e18;
    while (L + 1 < R) {
        int64_t mid = (L + R) / 2;
        (check(tn, mid).second <= k ? R : L) = mid;
    }
    auto v = check(tn, R);
    return round(v.first - v.second * R);
}
