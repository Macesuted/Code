/**
 * @file 101808B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 4005

uint64_t val[maxn][maxn], a[maxn];
mt19937_64 rnd(114514);

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= 2 * n; i++)
        for (int j = i; j <= 2 * n; j++) val[i][j] = rnd();
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if (x > y) swap(x, y);
        a[i] = val[x][y];
    }
    map<uint64_t, int> cnt;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        uint64_t cur = 0;
        for (int j = i; j <= n; j++) ans += cnt[cur += a[j]]++;
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

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}