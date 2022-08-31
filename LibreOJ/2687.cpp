/**
 * @file 2687.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-31
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

#define maxn 70005

int f[maxn][11], g[maxn][11][11];
bool mu[maxn];

void solve(void) {
    int n, cnt = 0;
    string s;
    cin >> n >> s, s = " " + s;
    bool non = true;
    for (int i = 1; i <= n; i++)
        if (s[i] == 'e')
            cnt += (non = true);
        else
            mu[i] = non, non = false;
    memset(f, 0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g));
    f[0][s[1] - 'a'] = 0;
    for (int i = 1, l = 0; i <= n; l = i, i++) {
        while (s[i] == 'e') i++;
        for (int j = 0; j <= 10; j++) {
            f[i][j] = min(f[l][s[i] - 'a'] + 2, g[l][s[i] - 'a'][s[i] - 'a'] + 2);
            if (j != s[i] - 'a' && !mu[i]) f[i][j] = min(f[i][j], f[l][j]);
            if (j != s[i] - 'a') f[i][j] = min(f[i][j], g[l][s[i] - 'a'][j]);
            for (int k = 0; k <= 10; k++) {
                g[i][j][k] = min(f[l][s[i] - 'a'] + 5, g[l][s[i] - 'a'][s[i] - 'a'] + 5);
                if (j != s[i] - 'a') g[i][j][k] = min({g[i][j][k], f[l][j] + 3, g[l][j][s[i] - 'a'] + 3});
                if (k != s[i] - 'a') g[i][j][k] = min(g[i][j][k], g[l][s[i] - 'a'][k] + 3);
                if (j != s[i] - 'a' && k != s[i] - 'a') g[i][j][k] = min(g[i][j][k], g[l][j][k] + 1);
            }
        }
    }
    cout << f[n][10] + 2 * cnt - 2 << endl;
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