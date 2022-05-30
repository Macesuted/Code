/**
 * @file 1402.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 50005

typedef pair<int, int> pii;

set<int> graph[maxn];
int deg[maxn], f[maxn];
bool vis[maxn];
set<pii> S;

void solve(void) {
    int n, k, ans = 1;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> deg[i], S.emplace(deg[i], i);
        for (int j = 0, x; j < deg[i]; j++) cin >> x, graph[i].insert(x);
    }
    while (!S.empty()) {
        int p = S.begin()->second;
        S.erase(S.begin()), vis[p] = true;
        vector<int> pnt;
        for (auto i : graph[p])
            if (!vis[i]) pnt.push_back(i);
        int c = pnt.size();
        for (int i = 0; i < c; i++) {
            f[i] = 1 << i;
            for (int j = 0; j < c; j++)
                if (graph[pnt[i]].count(pnt[j])) f[i] |= 1 << j;
        }
        for (int S = 0; S < (1 << c); S++) {
            if (__builtin_popcount(S) < ans) continue;
            bool chk = true;
            for (int i = 0; i < c; i++)
                if (S >> i & 1) chk &= ((f[i] & S) == S);
            if (chk) ans = max(ans, __builtin_popcount(S) + 1);
        }
        for (auto i : pnt) S.erase({deg[i], i}), S.insert({--deg[i], i});
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    freopen("poldev.in", "r", stdin), freopen("poldev.out", "w", stdout);
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