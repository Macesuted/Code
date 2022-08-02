/**
 * @file 270.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 200005
#define base 31
#define mod 19260817

int64_t hs[maxn], pw[maxn];
int lef[maxn], rig[maxn];
bool f[maxn];

int64_t getHash(int l, int r) { return (hs[r] + mod - hs[l - 1] * pw[r - l + 1] % mod) % mod; }

void solve(void) {
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;
    pw[0] = 1;
    for (int i = 1; i <= n; i++) hs[i] = (hs[i - 1] * base + (s[i] - 'a')) % mod, pw[i] = pw[i - 1] * base % mod;
    f[n] = true;
    for (int i = 1; i <= n; i++) lef[i] = i - 1, rig[i] = i + 1;
    for (int i = n, lp = i - 1; i; i--) {
        if (!f[i]) continue;
        lp = min(lp, i - 1);
        while (lp && f[lp]) lp--;
        for (int p = lp; p >= i - p; p = lef[p])
            if (getHash(p - (i - p) + 1, p) == getHash(p + 1, i))
                f[p] = true, lef[rig[p]] = lef[p], rig[lef[p]] = rig[p];
        }
    for (int i = 1; !f[i - 1]; i++) cout << s[i];
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
