/**
 * @file 51208F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-16
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

#define maxn 4005
#define mod 998244353

int id[maxn], rk[maxn], indeg[maxn];
int64_t a[maxn], b[maxn], f[maxn][maxn];
vector<int> graph[maxn], rgraph[maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }
int64_t& F(int x, int y) { return x <= y ? f[x][y] : f[y][x]; }

void solve(void) {
    int n, m;
    cin >> n >> m;
    int64_t inv2 = Inv(2);
    for (int i = 1; i <= n; i++)
        cin >> a[i], b[i] = a[i] * inv2 % mod, a[i] = a[i] * b[i] % mod, graph[0].push_back(i), rgraph[i].push_back(0),
                     indeg[i]++;
    for (int i = 1, x, y; i <= m; i++) cin >> x >> y, graph[x].push_back(y), rgraph[y].push_back(x), indeg[y]++;
    queue<int> que;
    que.push(0), n = -1;
    while (!que.empty()) {
        int p = id[++n] = que.front();
        rk[p] = n, que.pop();
        for (auto i : graph[p])
            if (!--indeg[i]) que.push(i);
    }
    f[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        int p = id[i];
        sort(rgraph[p].begin(), rgraph[p].end());
        for (auto x = rgraph[p].begin(); x != rgraph[p].end(); x++) {
            for (auto y = x; y != rgraph[p].end(); y++) f[p][p] = (f[p][p] + f[*x][*y] * a[p]) % mod;
            for (int y = 0; y <= n; y++)
                if (p != y) F(p, y) = (F(p, y) + F(*x, y) * b[p] * (1 + (*x == y))) % mod;
        }
    }
    int64_t ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) ans = (ans + f[i][j]) % mod;
    cout << ans * Pow(2, n) % mod << endl;
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