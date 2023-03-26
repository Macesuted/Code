/**
 * @file 1809F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-26
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

int a[maxn], b[maxn];

void solve(void) {
    int n;
    int64_t k;
    cin >> n >> k;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], ans += 2 * a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    queue<int64_t> que;
    for (int i = 1; i <= n; i++)
        if (b[i] == 1) {
            if (!que.empty()) ans -= min(que.back(), k);
            que.push(a[i]);
        } else if (!que.empty())
            que.back() += a[i];
    if (que.empty()) {
        for (int i = 1; i <= n; i++) cout << ans << ' ';
        cout << endl;
        return;
    }
    ans -= min(que.back(), k);
    cout << ans << ' ';
    for (int i = 1; i < n; i++) {
        if (b[i] == 1)
            ans += min(que.front(), k) - a[i], que.pop(), que.push(a[i]);
        else
            ans += min(que.back(), k), que.back() += a[i], ans -= min(que.back(), k);
        cout << ans << ' ';
    }
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