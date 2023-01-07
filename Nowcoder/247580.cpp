/**
 * @file 247580.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005

typedef pair<int64_t, int> pli;

vector<vector<int>> graph;
int a[maxn];
int64_t f[maxn], g[maxn];

void solve(void) {
    int n;
    cin >> n, graph.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2, p; i <= n; i++) cin >> p, graph[p].push_back(i);
    for (int i = n; i; i--) {
        f[i] = a[i];
        if (graph[i].empty()) continue;
        vector<pli> cac;
        int64_t sum = 0;
        for (auto j : graph[i]) cac.emplace_back(f[j], j), sum += f[j], g[i] += g[j];
        sort(cac.begin(), cac.end());
        if (sum - cac.back().first >= cac.back().first) {
            f[i] += sum % 2, g[i] += sum / 2;
        } else {
            g[i] += sum - cac.back().first;
            int64_t v = 2 * cac.back().first - sum;
            for (auto j : graph[i])
                if (j != cac.back().second) {
                    int64_t x = min(g[j], v / 2);
                    v -= 2 * x, g[i] += x;
                }
            f[i] += v;
        }
    }
    cout << f[1] + g[1] << endl;
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