/**
 * @file arc147_e.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-04
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

#define maxn 300005

typedef pair<int, int> pii;

priority_queue<int, vector<int>, less<int>> A, B;
priority_queue<int, vector<int>, greater<int>> uB;
priority_queue<pii, vector<pii>, less<pii>> que;

void solve(void) {
    int n, ans = 0;
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if (x < y)
            A.push(x), B.push(y);
        else
            ans++, que.emplace(x, y);
    }
    while (!B.empty()) {
        int b = B.top();
        B.pop();
        if (!A.empty() && A.top() >= b) {
            A.pop();
            continue;
        }
        while (!que.empty() && que.top().first >= b) uB.push(que.top().second), que.pop();
        if (uB.empty()) return cout << -1 << endl, void();
        ans--, B.push(uB.top()), uB.pop();
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}