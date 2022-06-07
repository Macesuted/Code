/**
 * @file 1601D.cpp
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

#define maxn 500005

typedef pair<int, int> pii;

pii a[maxn];

void solve(void) {
    int n, d, cnt = 0;
    cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1,
         [](pii a, pii b) { return make_pair(max(a.first, a.second), a.first) < make_pair(max(b.first, b.second), b.first); });
    for (int i = 1; i <= n; i++)
        if (a[i].first >= d) cnt++, d = max(d, a[i].second);
    cout << cnt << endl;
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