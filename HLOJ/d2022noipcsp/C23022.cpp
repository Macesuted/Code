/**
 * @file C23022.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

bool mem1;

#define maxn 3000005
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

int n, siz[maxn], dfni[maxn], dfno[maxn], a[maxn];
int64_t f[maxn], fac[maxn], ifac[maxn];
vector<int> graph[maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }
void add(int l, int r, int v) { return a[l] = Mod(a[l] + v), a[r + 1] = Mod(a[r + 1] + mod - v), void(); }
int dfnt = 0;
void dfs(int p, int pre = -1) {
    siz[p] = 1, dfni[p] = ++dfnt;
    for (auto i : graph[p])
        if (i != pre) dfs(i, p), siz[p] += siz[i], add(dfni[i], dfno[i], f[n - siz[i]]);
    dfno[p] = dfnt;
    add(1, dfni[p] - 1, f[siz[p]]), add(dfno[p] + 1, n, f[siz[p]]);
    return;
}

void solve(void) {
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1; i < n; i++) f[i] = i * fac[n] % mod * ifac[i + 1] % mod * fac[i] % mod;
    dfs(1);
    for (int i = 1; i <= n; i++) a[i] = Mod(a[i] + a[i - 1]);
    for (int i = 1; i <= n; i++) cout << Mod(a[dfni[i]] + f[n - 1]) << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("black.in", "r", stdin), freopen("black.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}