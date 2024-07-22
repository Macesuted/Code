/**
 * @file 7450.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005
#define endl '\n'

struct Frac {
    int64_t u, d;
    Frac(void) { u = 0, d = 1; }
    Frac(int64_t u_, int64_t d_) { u = u_, d = d_; }
    Frac operator+(const Frac& o) const {
        int64_t ud = d / __gcd(d, o.d) * o.d, uu = ud / d * u + ud / o.d * o.u;
        int64_t x = __gcd(ud, uu);
        return Frac{uu / x, ud / x};
    }
    bool operator<(const Frac& o) const {
        int64_t ud = d / __gcd(d, o.d) * o.d;
        return ud / d * u < ud / o.d * o.u;
    }
};

Frac f[maxn];
vector<vector<int>> graph;

void dfs(int p, int pre = -1) {
    for (auto i : graph[p])
        if (i != pre) f[i] = f[p] + f[i], dfs(i, p);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    graph.clear(), graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i <= n; i++) f[i].u = 15, cin >> f[i].d;
    dfs(1);
    Frac ans(0, 1);
    for (int i = 1; i <= n; i++)
        if (ans < f[i]) ans = f[i];
    cout << ans.u << '/' << ans.d << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}
