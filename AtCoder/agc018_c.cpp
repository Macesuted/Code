/**
 * @file agc018_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-12
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
int64_t f[maxn], g[maxn];

void solve(void) {
    int x, y, z, n;
    cin >> x >> y >> z, n = x + y + z;
    int64_t tot = 0, ans = INT64_MIN;
    for (int i = 1, x; i <= n; i++) cin >> x >> a[i].first >> a[i].second, tot += x, a[i].first -= x, a[i].second -= x;
    sort(a + 1, a + n + 1, [](pii a, pii b) { return a.first - a.second > b.first - b.second; });
    priority_queue<int, vector<int>, greater<int>> que;
    for (int i = 1; i <= n; i++) {
        que.push(a[i].first), f[i] = f[i - 1] + a[i].first;
        if ((int)que.size() > y) f[i] -= que.top(), que.pop();
    }
    while (!que.empty()) que.pop();
    for (int i = n; i; i--) {
        que.push(a[i].second), g[i] = g[i + 1] + a[i].second;
        if ((int)que.size() > z) g[i] -= que.top(), que.pop();
    }
    for (int i = y; i <= n - z; i++) ans = max(ans, f[i] + g[i + 1]);
    cout << ans + tot << endl;
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