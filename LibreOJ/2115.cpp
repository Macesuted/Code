/**
 * @file 2115.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-04
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

#define maxn 100005
#define mod 1000000007

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

vector<int> graph[maxn];
int indeg[maxn], ind[maxn];
int64_t f[maxn];

void solve(void) {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), indeg[y]++;
    int64_t ans = 1, prod = 1;
    for (int i = 2; i <= n; i++) ans = ans * (indeg[i] + (i == t)) % mod, prod = prod * indeg[i] % mod, ind[i] = indeg[i];
    queue<int> que;
    f[t] = prod, que.push(1);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        f[p] = f[p] * Inv(indeg[p]) % mod;
        for (auto i : graph[p]) {
            f[i] = (f[i] + f[p]) % mod;
            if (!--ind[i]) que.push(i);
        }
    }
    cout << (ans + mod - f[s]) % mod << endl;
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
