/**
 * @file 108199C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

using pii = pair<int, int>;

unordered_set<int> graph[maxn];
vector<int> ngraph[maxn];
set<pii> avai[maxn];
int ans[maxn], dist[maxn], pre[maxn];
bool lck[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) avai[n + i].emplace(1, n);
    for (int i = 1, m, x; i <= n; i++) {
        cin >> m;
        while (m--) {
            cin >> x;
            graph[i].insert(n + x);

            auto p = --avai[n + x].lower_bound({i + 1, 0});
            auto [l, r] = *p;
            avai[n + x].erase(p);
            if (l < i) avai[n + x].emplace(l, i - 1);
            if (i < r) avai[n + x].emplace(i + 1, r);
        }
    }

    auto avaiLef = [&](int y) -> int {
        for (auto [l, r] : avai[y])
            for (int x = l; x <= r; x++)
                if (ans[x] && !lck[ans[x]]) return x;
        return 0;
    };

    unordered_set<int> rig;
    for (int i = 1; i <= n; i++) rig.insert(n + i);
    for (int x = 1; x <= n; x++) {
        for (auto y : rig)
            if (!graph[x].count(y)) {
                ans[x] = y, ans[y] = x, rig.erase(y);
                break;
            }
        if (ans[x]) continue;

        for (auto y : graph[x]) lck[y] = true;

        for (auto i : graph[x])
            for (auto j : graph[x])
                if (ans[i] && i != j && !graph[ans[i]].count(j)) ngraph[i].push_back(j);

        for (auto y2 : graph[x]) {
            int x1 = avaiLef(y2);
            if (!x1) continue;
            int y1 = ans[x1];

            queue<int> que;
            que.push(y2);
            for (auto y : graph[x]) dist[y] = INT_MAX;
            dist[y2] = pre[y2] = 0;
            while (!que.empty()) {
                int p = que.front();
                que.pop();
                for (auto q : ngraph[p])
                    if (dist[q] > dist[p] + 1) dist[q] = dist[p] + 1, pre[q] = p, que.push(q);
            }

            int y = 0;
            for (auto ty : graph[x])
                if (!ans[ty] && dist[ty] != INT_MAX) y = ty;
            if (!y) continue;

            vector<int> lnk;
            while (y) lnk.push_back(y), y = pre[y];
            lnk.push_back(y1);
            reverse(lnk.begin(), lnk.end());
            for (int i = lnk.size() - 1; i; i--) {
                int x = ans[lnk[i - 1]], y = lnk[i];
                ans[x] = y, ans[y] = x;
            }
            ans[x] = lnk[0], ans[lnk[0]] = x;
            rig.erase(lnk.back());

            break;
        }

        if (!ans[x]) return cout << -1 << endl, void();

        for (auto y : graph[x]) lck[y] = false, ngraph[y].clear();
    }

    for (int i = 1; i <= n; i++) cout << ans[i] - n << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}