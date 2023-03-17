/**
 * @file 217.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-17
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

#define maxn 2005
#define mod 1000000007

string a[maxn];
int fa[maxn * 2];

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = " " + a[i];
    for (int i = 1; i <= n + m; i++) fa[i] = i;
    int64_t ans = 1;
    if (n & 1) {
        int c = (n + 1) / 2;
        bool chk = true;
        for (int i = 1; i <= m; i++) chk &= (a[c][i] == a[c][m - i + 1]);
        ans *= (1 + !chk);
    }
    if (m & 1) {
        int c = (m + 1) / 2;
        bool chk = true;
        for (int i = 1; i <= n; i++) chk &= (a[i][c] == a[n - i + 1][c]);
        ans *= (1 + !chk);
    }
    for (int u = 1, d = n; u < d; u++, d--)
        for (int i = 1, j = m; i < j; i++, j--) {
            map<char, int> c;
            c[a[u][i]]++, c[a[u][j]]++, c[a[d][i]]++, c[a[d][j]]++;
            if (c.size() == 4) {
                ans = ans * 12 % mod;
                if (getfa(u) != getfa(n + i)) ans = ans * 2 % mod;
                fa[getfa(u)] = getfa(n + i);
            } else if (c.size() == 3)
                ans = ans * 12 % mod;
            else if (c.size() == 2 && c.begin()->second == 2)
                ans = ans * 6 % mod;
            else if (c.size() == 2)
                ans = ans * 4 % mod;
        }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("square.in", "r", stdin), freopen("square.out", "w", stdout);
#endif
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