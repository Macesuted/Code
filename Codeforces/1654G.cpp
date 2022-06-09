/**
 * @file 1654G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-09
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

int h[maxn], d[maxn], b[maxn];
vector<int> graph[maxn], nodes[maxn];

void solve(void) {
    int n;
    cin >> n;
    memset(h, 0xff, sizeof(h));
    {
        static queue<int> que;
        for (int i = 1, t; i <= n; i++) {
            cin >> t;
            if (t) h[i] = 0, que.push(i);
        }
        for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p])
                if (!~h[i]) h[i] = h[p] + 1, que.push(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        bool check = false;
        for (auto j : graph[i])
            if (h[i] == h[j]) check = true;
        if (check) nodes[h[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) d[i] = h[i];
    static queue<pii> que;
    for (int i = 0; i <= n; i++) {
        if (nodes[i].empty()) continue;
        for (int j = 1; j <= n; j++) b[j] = 0x3f3f3f3f;
        for (auto j : nodes[i]) que.emplace(j, b[j] = 0);
        while (!que.empty()) {
            int p, v;
            tie(p, v) = que.front(), que.pop();
            if (!v) d[p] = max(d[p], h[p] * 2 - i);
            for (auto i : graph[p]) {
                if (h[i] == h[p] && v + 1 < b[i]) que.emplace(i, b[i] = v + 1);
                if (h[i] > h[p] && max(0, v - 1) < b[i]) que.emplace(i, b[i] = max(0, v - 1));
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << d[i] << ' ';
    cout << endl;
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