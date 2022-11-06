/**
 * @file 3953.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 10005
#define maxsv 10000005
#define maxlgn 48
#define mod 998244353

bool notPrime[maxsv];
vector<int> prime;
vector<vector<int>> graph;
int64_t f[maxn][maxlgn][maxlgn], g[maxlgn][maxlgn], h[maxlgn];

int64_t Mod(int64_t x) { return x >= mod ? x - mod : x; }

void dfs1(int p, int dep = 1, int pre = -1) {
    int MAX = (maxlgn - 1) / dep;
    if (~pre)
        for (int i = 0; i <= MAX; i++) f[p][i][i] = 1;
    else
        for (int i = 0; i <= MAX; i++) f[p][i][0] = 1;
    for (auto x : graph[p]) {
        if (x == pre) continue;
        dfs1(x, dep + 1, p);
        for (int i = 0; i <= MAX; i++)
            for (int j = 0; i + j < maxlgn; j++)
                if (f[p][i][j])
                    for (int k = 0; i + j + k < maxlgn; k++) g[i][j + k] = Mod(g[i][j + k] + f[p][i][j] * f[x][i][k] % mod);
        for (int j = 0; j <= MAX; j++)
            for (int k = 0; k < maxlgn; k++) f[p][j][k] = g[j][k], g[j][k] = 0;
    }
    if (~pre)
        for (int i = 1; i < maxlgn; i++)
            for (int j = 0; j < maxlgn; j++) f[p][i][j] = Mod(f[p][i][j] + f[p][i - 1][j]);
    return;
}
int dfs2(vector<int>::iterator p, int64_t val, int64_t sum) {
    if (p == prime.end() || val < (int64_t)*p * *p) return val % mod * sum % mod;
    int64_t ans = dfs2(p + 1, val, sum);
    val /= (int64_t)*p * *p;
    for (int i = 2; val; i++, val /= *p) ans = Mod(ans + dfs2(p + 1, val, sum * h[i] % mod));
    return ans;
}

void solve(void) {
    int n;
    int64_t k;
    cin >> n >> k;
    graph.resize(n + 1);
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    dfs1(1);
    for (int i = maxlgn - 1; i; i--)
        for (int j = 0; j < maxlgn; j++) f[1][i][j] = Mod(f[1][i][j] + mod - f[1][i - 1][j]);
    for (int i = 0; i < maxlgn; i++)
        for (int j = 0; i + j < maxlgn; j++) h[i + j] = Mod(h[i + j] + f[1][i][j]);
    cout << dfs2(prime.begin(), k, 1) << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("number.in", "r", stdin), freopen("number.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    notPrime[1] = true;
    for (int i = 2; i < maxsv; i++) {
        if (!notPrime[i]) prime.push_back(i);
        for (auto j = prime.begin(); i * *j < maxsv; j++) {
            notPrime[i * *j] = true;
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
