/**
 * @file 100431G.cpp
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

#define maxn 200005

using pii = pair<int, int>;

vector<pii> graph[maxn];
int pre[maxn], a[maxn], dfni[maxn], head[maxn], tail[maxn];
bool ques[maxn];

int dfnt = 0;
void dfs(int p) {
    dfni[p] = ++dfnt;
    for (auto& [d, q] : graph[p]) dfs(q), d = dfni[q];
    return;
}

void solve(void) {
    int n;
    cin >> n;

    for (int i = 1, op; i <= n; i++) {
        cin >> op >> pre[i];
        if (op == +1)
            cin >> a[i], graph[tail[pre[i]]].emplace_back(0, i), tail[i] = i;
        else
            ques[i] = true, tail[i] = tail[pre[i]];
    }

    dfs(0);

    head[0] = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = head[pre[i]];
        if (!ques[i]) continue;
        head[i] = prev(lower_bound(graph[head[i]].begin(), graph[head[i]].end(), pii{dfni[tail[i]] + 1, 0}))->second;
        cout << a[head[i]] << endl;
    }

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("queue.in", "r", stdin), freopen("queue.out", "w", stdout);
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