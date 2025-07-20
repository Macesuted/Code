/**
 * @file arc202_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-20
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

void solve(void) {
    int n;
    cin >> n;
    stack<int> S;
    int64_t ans = 0;

    auto push = [&](int v) -> void {
        while (!S.empty() && S.top() == v) S.pop(), v++;
        return S.push(v);
    };

    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        while (!S.empty() && S.top() < x) {
            int t = S.top();
            S.pop();
            int cur = x;
            if (!S.empty()) cur = min(cur, S.top());
            cur -= t;
            t += cur, ans += cur;
            push(t);
        }
        push(x);
    }
    while (S.size() > 1) {
        int t = S.top();
        S.pop();
        ans += S.top() - t;
        S.top()++;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}