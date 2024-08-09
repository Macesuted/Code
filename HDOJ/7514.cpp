/**
 * @file 7514.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

int a[maxn];

void solve(void) {
    int n, x, k;
    cin >> n >> x >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    k = min(k, n);
    priority_queue<int, vector<int>, greater<int>> que;
    for (int i = 1; i <= k; i++) que.push(a[i]);
    int ans = k;
    while (ans <= n && x > 0) {
        que.push(a[++ans]);
        x -= que.top(), que.pop();
    }
    cout << ans - 1 << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}