/**
 * @file 1729G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-12
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
#define mod 1000000007

int f[maxn], g[maxn];

void solve(void) {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    s = " " + s, t = " " + t;
    auto chk = [&](int p) {
        for (int i = 1; i <= m; i++)
            if (t[i] != s[p + i - 1]) return false;
        return true;
    };
    f[0] = 0, g[0] = 1;
    for (int i = 1; i <= n; i++)
        if (i < m || !chk(i - m + 1))
            f[i] = f[i - 1], g[i] = g[i - 1];
        else {
            f[i] = INT_MAX, g[i] = 0;
            for (int j = i - m + 1; j <= i; j++)
                if (j >= m && chk(j - m + 1)) {
                    if (f[j - m] + 1 < f[i]) f[i] = f[j - m] + 1, g[i] = 0;
                    if (f[j - m] + 1 == f[i]) g[i] = (g[i] + g[j - m]) % mod;
                }
        }
    cout << f[n] << ' ' << g[n] << endl;
    return;
}

bool mem2;

int main() {
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