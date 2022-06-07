/**
 * @file 1654F.cpp
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

#define maxn 262149

int sa[maxn], rk[maxn], ork[maxn], id[maxn], buc[maxn], val[maxn];

void solve(void) {
    int n;
    string s, t;
    cin >> n >> s, n = 1 << n, t.resize(n);
    int m = max(256, n);
    for (int i = 0; i < n; i++) buc[rk[i] = s[i]]++;
    for (int i = 1; i < m; i++) buc[i] += buc[i - 1];
    for (int i = n - 1; ~i; i--) sa[--buc[rk[i]]] = i;
    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; i++) id[i] = sa[i] ^ l;
        for (int i = 0; i < m; i++) buc[i] = 0;
        for (int i = 0; i < n; i++) buc[val[i] = rk[id[i]]]++;
        for (int i = 1; i < m; i++) buc[i] += buc[i - 1];
        for (int i = n - 1; ~i; i--) sa[--buc[val[i]]] = id[i];
        for (int i = 0; i < n; i++) ork[i] = rk[i];
        m = -1;
        for (int i = 0; i < n; i++) {
            if (!i || ork[sa[i]] != ork[sa[i - 1]] || ork[sa[i] ^ l] != ork[sa[i - 1] ^ l]) m++;
            rk[sa[i]] = m;
        }
        m++;
    }
    int j = sa[0];
    for (int i = 0; i < n; i++) t[i ^ j] = s[i];
    cout << t << endl;
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