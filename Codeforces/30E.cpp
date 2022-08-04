/**
 * @file 30E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-07
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

#define maxn 100005

typedef pair<int, int> pii;

int nxt[maxn], par[maxn];
pii f[maxn];

void solve(void) {
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;
    nxt[n] = n + 1;
    for (int i = n - 1, p = n + 1; i; i--) {
        while (p != n + 1 && s[p - 1] != s[i]) p = nxt[p];
        nxt[i] = (p -= (s[p - 1] == s[i]));
    }
    for (int i = 1, p = n + 1; i <= n; i++) {
        while (p != n + 1 && s[p - 1] != s[i]) p = nxt[p];
        f[i].first = n - (p -= (s[p - 1] == s[i])) + 1, f[i].second = i - f[i].first + 1;
    }
    for (int i = 1; i <= n; i++) f[i] = max(f[i], f[i - 1]);
    for (int i = 1, l = 1, r = 0; i <= n; i++) {
        if (r >= i) par[i] = min(par[l + r - i], r - i + 1);
        while (i - par[i] >= 1 && i + par[i] <= n && s[i - par[i]] == s[i + par[i]]) par[i]++;
        if (i + par[i] - 1 >= r) l = i - par[i] + 1, r = i + par[i] - 1;
    }
    int ans = 0, pos = -1;
    for (int i = 1; i <= n; i++)
        if (par[i] * 2 - 1 > ans) ans = par[i] * 2 - 1, pos = -i;
    for (int i = 1; i <= n; i++) {
        int val = par[i] * 2 - 1 + f[i - par[i]].first * 2;
        if (f[i - par[i]].second + f[i - par[i]].first - 1 < i - par[i] + 1 &&
            i + par[i] - 1 < n - f[i - par[i]].first + 1 && val > ans)
            ans = val, pos = i;
    }
    if (pos < 0)
        pos = -pos, cout << 1 << endl << pos - par[pos] + 1 << ' ' << 2 * par[pos] - 1 << endl;
    else
        cout << 3 << endl
             << f[pos - par[pos]].second << ' ' << f[pos - par[pos]].first << endl
             << pos - par[pos] + 1 << ' ' << 2 * par[pos] - 1 << endl
             << n - f[pos - par[pos]].first + 1 << ' ' << f[pos - par[pos]].first << endl;
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