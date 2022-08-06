/**
 * @file 748.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-06
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

#define maxn 305
#define mod 998244353

int f[2][maxn][maxn], fail[maxn];
stack<int> S;

void solve(void) {
    int n, m;
    string s;
    cin >> n >> m >> s;
    memset(f[0], 0, sizeof(f[0])), f[0][0][0] = 1;
    for (int i = 0; i <= n; i++) {
        fail[i] = (S.empty() ? -1 : S.top());
        if (i < n) s[i] == '0' ? S.push(i) : (S.empty() ? void() : S.pop());
    }
    for (int i = 0; i < (n + 2 * m); i++) {
        bool t = i & 1;
        memset(f[!t], 0, sizeof(f[!t]));
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= n; k++) {
                if (!f[t][j][k]) continue;
                if (k < n && s[k] == '0')
                    f[!t][j][k + 1] = (f[!t][j][k + 1] + f[t][j][k]) % mod;
                else
                    f[!t][j + 1][k] = (f[!t][j + 1][k] + f[t][j][k]) % mod;
                if (k < n && s[k] == '1')
                    f[!t][j][k + 1] = (f[!t][j][k + 1] + f[t][j][k]) % mod;
                else if (j)
                    f[!t][j - 1][k] = (f[!t][j - 1][k] + f[t][j][k]) % mod;
                else if (~fail[k])
                    f[!t][j][fail[k]] = (f[!t][j][fail[k]] + f[t][j][k]) % mod;
            }
    }
    cout << f[(n + 2 * m) & 1][0][n] << endl;
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