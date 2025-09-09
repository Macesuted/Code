/**
 * @file 14303.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxm 200005

using pii = pair<int, int>;

void solve(void) {
    int m, n;
    cin >> m >> n;
    priority_queue<pii, vector<pii>, greater<pii>> que;
    for (int i = 1, l, r; i <= m; i++) cin >> l >> r, que.emplace(l, r);
    int ans = n;
    while (!que.empty()) {
        int r = que.top().first;
        priority_queue<int, vector<int>, greater<int>> rec;
        while (true) {
            while (!que.empty() && que.top().first <= r) rec.push(que.top().second), que.pop();
            while (!rec.empty() && rec.top() <= r) rec.pop();
            if (rec.empty()) break;
            ans--, r++, rec.pop();
        }
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
