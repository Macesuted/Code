/**
 * @file 316.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-10
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

#define maxn 2000005

typedef pair<int, int> pii;

int a[maxn], f[maxn], g[maxn];
bool vis[maxn];
vector<pii> vec;
stack<int> S;
vector<int> graph[maxn];

void dfs(int p) {
    int son = 0;
    vis[p] = true;
    for (auto i : graph[p]) {
        dfs(i);
        if (g[i] > g[son]) son = i;
    }
    g[p] = g[son] + 1, g[son] = 0;
    return;
}

void solve(void) {
    int n, m, T, ans = 0;
    cin >> n >> m >> T;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] <= T)
            S.push(i);
        else {
            while (!S.empty() && i - S.top() + a[S.top()] > T) S.pop();
            if (S.empty())
                ans++, f[i] = n + 1;
            else
                f[i] = S.top(), vec.emplace_back(f[i], i - 1);
        }
    }
    while (!S.empty()) S.pop();
    for (int i = n; i; i--) {
        while (!S.empty() && f[S.top()] > i) S.pop();
        if (!S.empty()) graph[S.top()].push_back(i);
        if (a[i] > T) S.push(i);
    }
    for (int i = n; i; i--)
        if (!vis[i]) dfs(i);
    sort(g + 1, g + n + 1, greater<int>());
    for (int i = 1; i <= m; i++) ans += g[i] - 1;
    cout << n - ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("lurien.in", "r", stdin), freopen("lurien.out", "w", stdout);
#endif
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