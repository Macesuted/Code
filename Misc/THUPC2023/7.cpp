/**
 * @file 7.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-05
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

#define maxn 100005

typedef pair<int, int> pii;

pii a[maxn];
int64_t f[maxn];
int vis[maxn];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1, [](pii a, pii b) { return (int64_t)a.second * b.first > (int64_t)b.second * a.first; });
    int m = a[1].first;
    for (int i = 1; i < m; i++) f[i] = INT64_MIN;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < m; j++) vis[j] = 0;
        for (int j = 0; j < m; j++) {
            if (vis[j]) continue;
            int64_t p = j, v = f[p];
            while (vis[p] < 3) {
                vis[p]++;
                v = f[p] = max(f[p], v);
                p += a[i].first;
                if (v != INT64_MIN) v += a[i].second - p / m * a[1].second;
                p %= m;
            }
        }
    }
    while (q--) {
        int64_t v;
        cin >> v;
        cout << (f[v % m] == INT64_MIN ? -1 : v / m * a[1].second + f[v % m]) << endl;
    }
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