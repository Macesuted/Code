/**
 * @file 199.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-21
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

#define maxn 1505

bitset<maxn> a[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        a[i].reset();
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) a[i][j] = (s[j] == 'Y');
    }
    int cnt = 0;
    for (int i = 2; i <= n; i++) cnt += ((a[i] & a[1]) == a[1]);
    if (cnt > 1) return cout << "N" << endl, void();
    for (int i = 2; i <= n; i++) {
        bitset<maxn> S = a[1] & a[i], T = a[1];
        for (int j = 2; j <= n; j++)
            if (i != j && ((a[j] & S) == S)) T |= a[j];
        if ((~T & ~S & a[i]).count()) return cout << "Y" << endl, void();
    }
    return cout << "N" << endl, void();
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("sort.in", "r", stdin), freopen("sort.out", "w", stdout);
#endif
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