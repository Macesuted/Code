/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007
// #define mod 998244353

#define maxn 205
#define maxlgn 10

int fac[maxn], inv[maxn];

inline int C(int n, int m) {
    if (n < m || n < 0 || m < 0) return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int power(int a, int x) {
    int ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

void INIT(int n) {
    fac[0] = inv[0] = 1;
    for (register int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
    inv[n] = power(fac[n], mod - 2);
    for (register int i = n - 1; i; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
    return;
}

int fa[maxn][maxlgn], dep[maxn], f[maxn][maxn];

vector<vector<int> > graph;

void dfs(int p, int pre = 0) {
    dep[p] = dep[pre] + 1;
    fa[p][0] = pre;
    for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) dfs(*i, p);
    return;
}
int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (register int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (register int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int F(int x, int y) {
    if (f[x][y]) return f[x][y];
    if (!x) return 1;
    if (!y) return 0;
    return f[x][y] = (F(x - 1, y) + F(x, y - 1)) * power(2, mod - 2) % mod;
}

void work(void) {
    int n;
    cin >> n;
    INIT(n + 3);
    graph.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to), graph[to].push_back(from);
    }
    int answer = 0;
    for (register int root = 1; root <= n; root++) {
        dfs(root);
        for (register int i = 1; i <= n; i++) {
            for (register int j = 1; j < i; j++) {
                int lca = LCA(i, j);
                answer = (answer + F(dep[i] - dep[lca], dep[j] - dep[lca])) % mod;
            }
        }
    }
    cout << answer * power(n, mod - 2) % mod << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    while (_--) work();
    return 0;
}