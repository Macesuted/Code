/**
 * @file 105053E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-03
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

#define maxn 1005

typedef pair<int, int> pii;

vector<int> graph[maxn * 2];
pii a[maxn];
bool vis[maxn * 2];

bool cross(pii a, pii b) {
    if (a.first > b.first) swap(a, b);
    return b.first < a.second && a.second < b.second;
}
void dfs(int p) {
    vis[p] = true;
    for (auto i : graph[p])
        if (!vis[i]) dfs(i);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= 2 * n; i++) {
        char c;
        int x;
        cin >> c >> x;
        if (c == '+')
            a[x].first = i;
        else
            a[x].second = i;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (cross(a[i], a[j]))
                graph[i].push_back(j + n), graph[j + n].push_back(i), graph[i + n].push_back(j), graph[j].push_back(i + n);
    for (int i = 1; i <= n; i++)
        if (!vis[i] && !vis[i + n]) dfs(i);
    for (int i = 1; i <= n; i++)
        if (vis[i] && vis[i + n]) return cout << '*' << endl, void();
    for (int i = 1; i <= n; i++) cout << "GS"[vis[i]];
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