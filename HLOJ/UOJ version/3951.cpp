/**
 * @file 3951.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

typedef tuple<int, int, int> tiii;

int cost[25], fa[25], deg[25];
vector<int> cnt[25];
int64_t ans[25][25];
vector<tiii> edges;

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    memset(ans, 0x3f, sizeof(ans));
    for (int i = 1; i <= m; i++) {
        int x, y, d;
        cin >> x >> y >> d;
        edges.emplace_back(d, x, y);
    }
    for (int i = 0; i < k; i++) cin >> cost[i];
    sort(cost, cost + k, greater<int>()), sort(edges.begin(), edges.end());
    for (int S = 0; S < (1 << n); S++) {
        for (int i = 0; i < n; i++) fa[i] = i, deg[i] = 0, cnt[i].clear();
        stack<int> wei;
        for (auto i : edges) {
            if (!(S >> get<1>(i) & 1) || !(S >> get<2>(i) & 1) || getfa(get<1>(i)) == getfa(get<2>(i))) continue;
            wei.push(get<0>(i)), fa[getfa(get<1>(i))] = getfa(get<2>(i)), deg[get<1>(i)]++, deg[get<2>(i)]++;
        }
        for (int i = 0; i < n; i++)
            if (S >> i & 1) cnt[deg[i]].push_back(i);
        if (cnt[0].empty() && cnt[1].size() == 2 && cnt[2].size() == (uint64_t)__builtin_popcount(S) - 2) {
            int x = cnt[1][0], y = cnt[1][1];
            int64_t cur = 0;
            for (int i = 0; !wei.empty(); i++) cur += max(wei.top() - cost[i], 0), wei.pop();
            ans[x][y] = min(ans[x][y], cur), ans[y][x] = min(ans[y][x], cur);
        }
    }
    int64_t answer = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) answer += ans[i][j];
    cout << answer << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("travel.in", "r", stdin), freopen("travel.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
