/**
 * @file 1738A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-30
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

pii a[maxn];

void solve(void) {
    int n, cnt[2] = {0, 0};
    cin >> n;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i].second, cnt[a[i].second]++;
    for (int i = 1; i <= n; i++) cin >> a[i].first, ans += a[i].first;
    sort(a + 1, a + n + 1, greater<pii>());
    for (int i = 1; i <= n; i++)
        if (cnt[!a[i].second] && (cnt[0] + cnt[1] > 1)) cnt[!a[i].second]--, ans += a[i].first;
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