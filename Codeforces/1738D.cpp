/**
 * @file 1738D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-30
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

#define maxn 100005

int b[maxn];
vector<int> pos[maxn];

void solve(void) {
    int n, k = 0;
    cin >> n;
    vector<int> ans;
    for (int i = 0; i <= n + 1; i++) pos[i].clear();
    for (int i = 1; i <= n; i++) cin >> b[i], pos[b[i]].push_back(i);
    queue<int> que;
    que.push(0), que.push(n + 1);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        if (pos[p].empty()) continue;
        if (p < pos[p].front())
            k = max(k, p);
        else
            for (auto i : pos[p]) k = max(k, i);
        int x = -1;
        for (auto i : pos[p])
            if (!pos[i].empty()) x = i;
        for (auto i : pos[p])
            if (i != x) ans.push_back(i);
        if (~x) ans.push_back(x), que.push(x);
    }
    cout << k << endl;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}