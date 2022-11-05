/**
 * @file arc146_d.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-05
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

#define maxn 200005

typedef pair<int, int> pii;

multimap<int, pii> rec[maxn];
int a[maxn];
queue<int> que;
bool inq[maxn];

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1, p, x, q, y; i <= k; i++)
        cin >> p >> x >> q >> y, rec[p].insert({x, {q, y}}), rec[q].insert({y, {p, x}});
    for (int i = 1; i <= n; i++)
        if (rec[i].count(a[i] = 1)) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop(), inq[p] = false;
        if (a[p] > m) return cout << -1 << endl, void();
        while (!rec[p].empty() && rec[p].begin()->first < a[p]) {
            auto [q, y] = rec[p].begin()->second;
            rec[p].erase(rec[p].begin());
            if (a[q] > y) continue;
            a[q] = max(a[q], y + 1);
            if (!inq[q]) que.push(q), inq[q] = true;
        }
        for (auto i = rec[p].begin(); i != rec[p].end() && i->first == a[p]; i++) {
            auto [q, y] = i->second;
            if (a[q] >= y) continue;
            a[q] = y;
            if (!inq[q]) que.push(q), inq[q] = true;
        }
    }
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) sum += a[i];
    cout << sum << endl;
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