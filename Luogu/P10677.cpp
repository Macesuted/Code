/**
 * @file P10677.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

pii a[maxn];
queue<int> que;
vector<pii> edge;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = i;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        que.push(a[i].second);
        while (--a[i].first) edge.emplace_back(a[i].second, que.front()), que.pop();
    }
    edge.emplace_back(que.front(), que.back());
    que.pop(), que.pop();
    for (auto [x, y] : edge) cout << x << ' ' << y << endl;
    edge.clear();
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