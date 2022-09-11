/**
 * @file agc050_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-11
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

#define maxn 1000005
#define maxlgn 22
#define mod 998244353

int f[maxlgn][maxn], g[maxlgn], lef[maxn], cnt[maxn];

int64_t Mod(int64_t a) { return a >= mod ? a - mod : a; }
void solve(void) {
    string s;
    cin >> s, s = " " + s;
    int n = s.size() - 1;
    int64_t ans = 1;
    for (int i = 1; i <= n; i++) ans = ans * (1 + (s[i] == '?')) % mod;
    bool chk = true;
    for (int i = 1; i <= n; i++) chk &= (s[i] != 'B');
    ans -= chk;
    for (int i = 1, last = 1; i <= n; i++) {
        lef[i] = last;
        if (s[i] == 'B') last = i;
    }
    for (int i = n; i; i--)
        if (s[i] == 'B') {
            f[0][i] = 1;
            break;
        } else if (s[i] == '?')
            f[0][i] = 1;
    for (int i = 0; i + 1 < maxlgn; i++) {
        for (int j = g[i] + 1; j <= n; j++)
            if (f[i][j] && lef[j] <= j - g[i])
                f[i + 1][lef[j]] = Mod(f[i + 1][lef[j]] + f[i][j]),
                      f[i + 1][j - g[i] + 1] = Mod(f[i + 1][j - g[i] + 1] + mod - f[i][j]);
        for (int j = 2; j <= n; j++) f[i + 1][j] = Mod(f[i + 1][j] + f[i + 1][j - 1]);
        for (int j = 1; j <= n; j++)
            if (s[j] == 'S') f[i + 1][j] = 0;
    }
    for (int j = 1; j <= n; j++) {
        for (int i = 0; i < maxlgn; i++) ans = Mod(ans + mod - f[i][j]);
        if (s[j] == 'B') break;
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

    for (int i = 2; i < maxn; i++) cnt[i] = 1 + cnt[(i + 1) / 2];
    g[0] = 2;
    for (int i = 1; i < maxlgn; i++) {
        g[i] = g[i - 1];
        while (g[i] < maxn && cnt[g[i]] <= i) g[i]++;
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}