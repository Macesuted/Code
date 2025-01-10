/**
 * @file 1468F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-05
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

#define maxn 100005

typedef pair<int, int> pii;

pii a[maxn];

void solve(void) {
    int n;
    cin >> n;

    map<pii, int> cnt;
    for (int i = 1, x, y, u, v; i <= n; i++) {
        cin >> x >> y >> u >> v;
        u -= x, v -= y;
        cnt[a[i] = {u / gcd(u, v), v / gcd(u, v)}]++;
    }

    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans += cnt[{-a[i].first, -a[i].second}];
    cout << ans / 2 << endl;

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