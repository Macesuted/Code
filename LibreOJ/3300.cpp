/**
 * @file 3300.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-20
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

#define maxn 1005

int64_t f[maxn][maxn], g[maxn], mod;

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void solve(void) {
    int n, x, m;
    cin >> n >> x >> mod >> m;
    f[0][0] = 1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j <= i; j++)
            f[i + 1][j] = (f[i + 1][j] + f[i][j] * j) % mod, f[i + 1][j + 1] = (f[i + 1][j + 1] + f[i][j] * (j + 1)) % mod;
    vector<int> vec;
    for (int i = 0; i <= m; i++) {
        vec.push_back(n - i + 1);
        g[i] = Pow(x, i) * Pow(x + 1, n - i) % mod;
        int v = i;
        for (auto &j : vec) {
            int c = __gcd(v, j);
            v /= c, g[i] = g[i] * (j /= c) % mod;
        }
    }
    int64_t ans = 0;
    for (int i = 0, a; i <= m; i++) {
        cin >> a;
        for (int j = 0; j <= i; j++) ans = (ans + a * f[i][j] % mod * g[j]) % mod;
    }
    cout << ans << endl;
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