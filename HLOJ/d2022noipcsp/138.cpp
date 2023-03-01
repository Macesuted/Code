/**
 * @file 138.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

typedef pair<int, int> pii;

vector<pii> spl;

void calc(int v) {
    spl.clear();
    for (int i = 2; i * i <= v; i++) {
        if (v % i == 0) spl.emplace_back(i, 0);
        while (v % i == 0) v /= i, spl.back().second++;
    }
    if (v > 1) spl.emplace_back(v, 1);
    return;
}
int dfs(int p, int d0, int d1) {
    d0 = min(d0, d1 + 1), d1 = min(d1, d0 + 1);
    if (p == 0) return d1;
    if (p == 1) return d0;
    int ans = p - 1 + d0;
    for (auto &i : spl) {
        if (!i.second) continue;
        int l = p / i.first * i.first, r = l + i.first;
        i.second--, ans = min(ans, dfs(p / i.first, d0 + p - l + 1, d1 + r - p)), i.second++;
    }
    return ans;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    if (n > m) swap(n, m);
    calc(m - n);
    cout << dfs(n, 0, 1) << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("operate.in", "r", stdin), freopen("operate.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}