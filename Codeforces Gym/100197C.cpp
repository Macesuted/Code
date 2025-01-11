/**
 * @file 100197C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-10
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
    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> que;
    int64_t ans = 0;
    for (int i = 1, x; i <= n; i++) cin >> x, que.push(x);
    while (que.size() > 1) {
        int64_t p = que.top();
        que.pop();
        int64_t q = que.top();
        que.pop();
        ans += p + q;
        que.push(p + q);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("huffman.in", "r", stdin), freopen("huffman.out", "w", stdout);
#endif
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