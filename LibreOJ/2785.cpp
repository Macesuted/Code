/**
 * @file 2785.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int n, a[maxn], b[maxn];
map<int, int> F[maxn];

int f(int p, int v) {
    if (F[p].count(v)) return F[p][v];
    int val = v;
    if ((p << 1) <= n) val = min(val, b[p << 1]);
    if ((p << 1 | 1) <= n) val = min(val, b[p << 1 | 1]);
    if (val == v) return F[p][v] = p;
    if (val == b[p << 1]) return F[p][v] = f(p << 1, v);
    if (v < b[p << 1]) return F[p][v] = min(f(p << 1, v), f(p << 1 | 1, v));
    return F[p][v] = f(f(p << 1, b[p << 1]) < f(p << 1 | 1, b[p << 1]) ? (p << 1 | 1) : (p << 1), v);
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i];
    for (int i = 1; i <= n; i++) {
        int v = a[i];
        if ((i << 1) <= n) v = min(v, a[i << 1]);
        if ((i << 1 | 1) <= n) v = min(v, a[i << 1 | 1]);
        if (v == a[i]) continue;
        if (v == a[i << 1]) {
            swap(a[i], a[i << 1]);
            continue;
        }
        swap(a[i], a[i << 1 | 1]);
        if (a[i << 1] > a[i << 1 | 1]) swap(a[i << 1], a[i << 1 | 1]);
        if (f(i << 1, a[i << 1]) > f(i << 1 | 1, a[i << 1])) swap(a[i << 1], a[i << 1 | 1]);
    }
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}