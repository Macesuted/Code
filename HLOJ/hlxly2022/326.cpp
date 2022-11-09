/**
 * @file 326.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-16
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

#define maxn 505
#define mod 998244353

typedef pair<int, int> pii;

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

vector<pii> graph[maxn];
vector<int> tree[maxn], f[maxn][maxn];
queue<int> que;
int n, dist[maxn], siz[maxn], g[maxn][maxn], h[maxn][maxn], inv[maxn];
bool vis[maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }

void dfs(int p) {
    for (auto i : tree[p]) dfs(i);
    memset(g, 0, sizeof(g)), g[0][0] = 1;
    for (auto q : tree[p]) {
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= siz[p]; j++)
                if (g[i][j])
                    for (int k = 1; k <= siz[q]; k++) h[i][j + k] = (h[i][j + k] + (int64_t)g[i][j] * f[q][i][k]) % mod;
        for (int i = 1, sum = 0; i <= n; i++) {
            for (int j = 1; j <= siz[q]; j++) sum = Mod(sum + f[q][i - 1][j]);
            for (int j = 0; j <= siz[p]; j++) h[i][j] = (h[i][j] + (int64_t)g[i][j] * sum) % mod;
        }
        for (int i = 1, sum = 0; i <= n; i++) {
            for (int j = 0; j <= siz[p]; j++) sum = Mod(sum + g[i - 1][j]);
            for (int j = 1; j <= siz[q]; j++) h[i][j] = (h[i][j] + (int64_t)f[q][i][j] * sum) % mod;
        }
        siz[p] += siz[q];
        memcpy(g, h, sizeof(g)), memset(h, 0, sizeof(h));
    }
    siz[p]++;
    for (int i = 0; i <= n; i++) f[p][i].resize(siz[p] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= n; j++)
            if (g[i][j])
                f[p][i][j + 1] = (f[p][i][j + 1] + (int64_t)g[i][j] * inv[j + 1]) % mod,
                            f[p][i + 1][1] = (f[p][i + 1][1] + (int64_t)g[i][j] * (1 + mod - inv[j + 1])) % mod;
    for (int j = 0; j <= n; j++) f[p][1][1] = Mod(f[p][1][1] + g[0][j]);
    return;
}

void solve(void) {
    int m;
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) cin >> u >> v >> w, graph[u].emplace_back(v, w);
    memset(dist, 0x3f, sizeof(dist)), dist[1] = 0, que.push(1);
    while (!que.empty()) {
        int p = que.front();
        que.pop(), vis[p] = false;
        for (auto i : graph[p])
            if (dist[i.first] > dist[p] + i.second) {
                dist[i.first] = dist[p] + i.second;
                if (!vis[i.first]) que.push(i.first), vis[i.first] = true;
            }
    }
    for (int i = 1; i <= n; i++)
        for (auto j : graph[i])
            if (dist[j.first] == dist[i] + j.second) tree[i].push_back(j.first);
    dfs(1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) ans = (ans + (int64_t)g[i][j] * i) % mod;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("B.in", "r", stdin), freopen("B.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 1; i < maxn; i++) inv[i] = Inv(i);

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}