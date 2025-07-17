/**
 * @file 100431H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-17
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

#define maxn 100005
#define maxc 15

using pli = pair<int64_t, int>;

int c[maxn], s[maxn], v[maxn], ans[maxn];
int64_t lst[maxn];
vector<int> t[maxn];
priority_queue<pli, vector<pli>, greater<pli>> dock[maxc], que;
set<pli> idle[maxc];

void solve(void) {
    int n, m, C;
    cin >> n >> m >> C;
    for (int i = 1, d; i <= n; i++) cin >> d >> c[i] >> s[i], que.emplace(d, -i);
    for (int i = 1, tc, x; i <= m; i++) {
        cin >> v[i] >> tc, lst[i] = 0;
        while (tc--) cin >> x, t[i].push_back(x), idle[x].emplace(lst[i], i);
    }

    while (!que.empty()) {
        int64_t tim = que.top().first;

        auto start = [&](int ship, int crane) {
            return que.emplace(lst[crane] = tim + s[ship] / v[crane] + (s[ship] % v[crane] > 0), ans[ship] = crane);
        };

        priority_queue<int, vector<int>, greater<int>> cranes, ships;
        while (!que.empty() && que.top().first == tim) {
            int e = que.top().second;
            que.pop();
            if (e < 0)
                ships.push(-e);
            else
                cranes.push(e);
        }

        while (!ships.empty()) {
            int ship = ships.top();
            ships.pop();

            if (idle[c[ship]].empty()) {
                dock[c[ship]].push({tim, ship});
                continue;
            }

            int crane = idle[c[ship]].begin()->second;
            for (int typ : t[crane]) idle[typ].erase({lst[crane], crane});
            start(ship, crane);
        }

        while (!cranes.empty()) {
            int crane = cranes.top();
            cranes.pop();

            pli choice = {INT64_MAX, 0};
            for (int typ : t[crane])
                if (!dock[typ].empty()) choice = min(choice, dock[typ].top());
            int ship = choice.second;
            if (ship) {
                dock[c[ship]].pop();
                start(ship, crane);
                continue;
            }
            for (int typ : t[crane]) idle[typ].emplace(lst[crane], crane);
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("seaport.in", "r", stdin), freopen("seaport.out", "w", stdout);
#endif
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