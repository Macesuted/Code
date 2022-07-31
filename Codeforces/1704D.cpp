/**
 * @file 1704D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-31
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

typedef __int128_t int128_t;

int128_t a[maxn];
map<int128_t, int> cnt;

void solve(void) {
    int n, m;
    cin >> n >> m;
    cnt.clear();
    for (int i = 1; i <= n; i++) {
        int64_t v;
        a[i] = 0;
        for (int j = 1; j <= m; j++) cin >> v, a[i] += (int128_t)v * j;
        cnt[a[i]]++;
    }
    int spe = -1;
    for (int i = 1; i <= n; i++)
        if (cnt[a[i]] == 1) spe = i;
    cout << spe << ' ' << (int64_t)(a[spe] - a[spe == 1 ? 2 : 1]) << endl;
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