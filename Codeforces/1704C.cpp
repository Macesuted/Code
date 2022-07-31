/**
 * @file 1704C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-31
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

#define maxm 100005

int a[maxm];
priority_queue<int, vector<int>, less<int>> que;

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> a[i];
    sort(a + 1, a + m + 1), que.push(a[1] + n - a[m] - 1);
    for (int i = 2; i <= m; i++) que.push(a[i] - a[i - 1] - 1);
    int tim = 0, ans = 0;
    while (!que.empty()) {
        int p = que.top();
        que.pop();
        if (p <= tim) continue;
        ans += max(1, p - tim - 1), tim += 4;
    }
    cout << n - ans << endl;
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