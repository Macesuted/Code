/**
 * @file 1859D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-08-19
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

#define maxn 200005

typedef pair<int, int> pii;

pii a[maxn];
map<int, int> f;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) cin >> a[i].first >> x >> y >> a[i].second;
    sort(a + 1, a + n + 1, greater<pii>());
    int tn = n;
    a[n = 0].second = INT_MAX;
    for (int i = 1; i <= tn; i++) {
        while (a[n].second <= a[i].second) n--;
        a[++n] = a[i];
    }
    f.clear(), f[0] = 0;
    for (int i = 1; i <= n; i++) f[a[i].first] = max(a[i].second, (--f.upper_bound(a[i].second))->second);
    int q;
    cin >> q;
    for (int i = 1, x; i <= q; i++) cin >> x, cout << max(x, (--f.upper_bound(x))->second) << ' ';
    cout << endl;
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