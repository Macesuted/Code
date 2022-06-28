/**
 * @file 3533.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-28
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

#define maxn 105
#define mod 998244353

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

int a[maxn], e[maxn], sum[maxn];
bool vis[maxn * maxn * 2];
int64_t mar[maxn][maxn], f[maxn * maxn * 2];
vector<vector<int>> graph;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];
    graph.resize(sum[n] + 1);
    for (int i = 1; i < n; i++) cin >> e[i];
    for (int i = 1; i < n; i++)
        for (int j = 1, x, y; j <= e[i]; j++) cin >> x >> y, graph[sum[i - 1] + x].push_back(sum[i] + y);
    for (int i = 1; i <= a[1]; i++) {
        memset(f, 0, sizeof(f)), memset(vis, 0, sizeof(vis));
        static queue<int> que;
        while (!que.empty()) que.pop();
        que.push(i), f[i] = 1;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p]) {
                if (!vis[i]) que.push(i);
                vis[i] = true, f[i] = (f[i] + f[p]) % mod;
            }
        }
        for (int j = 1; j <= a[n]; j++) mar[i][j] = f[sum[n - 1] + j];
    }
    int64_t ans = 1;
    for (int i = 1; i <= a[1]; i++) {
        int p = i;
        while (p <= a[1] && !mar[p][i]) p++;
        if (p > a[1]) {
            ans = 0;
            break;
        }
        if (p != i) ans = mod - ans;
        for (int j = 1; j <= a[1]; j++) swap(mar[i][j], mar[p][j]);
        ans = ans * mar[i][i] % mod;
        int64_t inv = Inv(mar[i][i]);
        for (int j = 1; j <= a[1]; j++) mar[i][j] = mar[i][j] * inv % mod;
        for (int j = 1; j <= a[1]; j++)
            if (i != j && mar[j][i])
                for (int k = a[1]; k >= i; k--) mar[j][k] = (mar[j][k] + mod - mar[j][i] * mar[i][k] % mod) % mod;
    }
    cout << ans << endl;
    graph.clear();
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("xpath.in", "r", stdin), freopen("xpath.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}