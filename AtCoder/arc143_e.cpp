/**
 * @file arc143_e.cpp
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

vector<int> graph[maxn], ograph[maxn];
int deg[maxn];
bool a[maxn], vis[maxn];
queue<int> que;
priority_queue<int, vector<int>, greater<int>> pque;
vector<int> ans;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x), deg[x]++, deg[y]++;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c, a[i] = (c == 'W');
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] <= 1) que.push(i);
    while (!que.empty()) {
        int p = que.front();
        que.pop(), vis[p] = true;
        for (auto i : graph[p]) {
            if (vis[i]) continue;
            if (a[p])
                ograph[p].push_back(i), a[i] ^= true;
            else
                ograph[i].push_back(p), a[p] ^= true;
            if (--deg[i] <= 1) que.push(i);
        }
    }
    for (int i = 1; i <= n; i++)
        if (!a[i]) return cout << -1 << endl, void();
    for (int i = 1; i <= n; i++) deg[i] = 0;
    for (int i = 1; i <= n; i++)
        for (auto j : ograph[i]) deg[j]++;
    for (int i = 1; i <= n; i++)
        if (!deg[i]) pque.push(i);
    while (!pque.empty()) {
        int p = pque.top();
        pque.pop(), ans.push_back(p);
        for (auto i : ograph[p])
            if (!--deg[i]) pque.push(i);
    }
    if ((int)ans.size() != n) return cout << -1 << endl, void();
    for (auto i : ans) cout << i << ' ';
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