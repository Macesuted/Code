/**
 * @file abc360_g.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

int a[maxn], f[maxn];
bool g[maxn];
set<pii> S;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    S.emplace(-1, 0);
    for (int i = 1; i <= n; i++) {
        auto p = --S.lower_bound({a[i], 0});
        f[i] = f[p->second] + 1, g[i] = (g[p->second] || (p->second + 1 < i && p->first + 1 < a[i]));
        while (p != S.begin() && f[(--p)->second] + 1 == f[i] && !g[i])
            g[i] |= (g[p->second] || (p->second + 1 < i && p->first + 1 < a[i]));
        p = S.lower_bound({a[i], 0});
        if (p != S.end() && p->first == a[i]) {
            if (f[p->second] == f[i]) continue;
            S.erase(p);
        }
        p = ++S.emplace(a[i], i).first;
        while (p != S.end() && f[p->second] < f[i]) p = S.erase(p);
    }
    int p = (--S.end())->second;
    g[p] |= (p < n);
    cout << f[p] + g[p] << endl;
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