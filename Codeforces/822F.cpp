/**
 * @file 822F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-05
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

#define maxn 105

typedef pair<int, int> pii;
typedef tuple<int, int, int, double> tiid;

vector<pii> graph[maxn];
vector<tiid> ans;

void dfs(int p, double tim = 0, int pre = -1) {
    double c = 2. / graph[p].size();
    for (auto i : graph[p])
        if (i.first != pre) {
            tim = tim + c;
            if (tim >= 2) tim -= 2;
            if (tim <= 1)
                ans.emplace_back(i.second, i.first, p, 1 - tim), dfs(i.first, tim + 1, p);
            else
                ans.emplace_back(i.second, p, i.first, 2 - tim), dfs(i.first, tim - 1, p);
        }
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].emplace_back(y, i), graph[y].emplace_back(x, i);
    dfs(1);
    cout << ans.size() << endl;
    for (auto i : ans) cout << "1 " << get<0>(i) << ' ' << get<1>(i) << ' ' << get<2>(i) << ' ' << get<3>(i) << endl;
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