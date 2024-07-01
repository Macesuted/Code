/**
 * @file 1987E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
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

#define maxn 5005

int fa[maxn], siz[maxn], lson[maxn], dep[maxn];
int64_t a[maxn], rest[maxn];
vector<int> son[maxn];
multimap<int, int>* choi[maxn];
int64_t ans;

void dfs(int p) {
    siz[p] = 1;
    if (son[p].empty()) {
        choi[p] = new multimap<int, int>();
        choi[p]->emplace(dep[p], p);
        rest[p] = INT64_MAX;
        return;
    }
    int64_t sum = lson[p] = 0;
    for (auto i : son[p]) {
        dep[i] = dep[p] + 1, dfs(i), siz[p] += siz[i], sum += a[i];
        if (!lson[p] || siz[lson[p]] < siz[i]) lson[p] = i;
    }
    choi[p] = choi[lson[p]];
    for (auto i : son[p]) {
        if (i == lson[p]) continue;
        for (auto j : *choi[i]) choi[p]->emplace(j.first, j.second);
        delete choi[i];
    }
    while (a[p] > sum) {
        int q = choi[p]->begin()->second;
        int64_t delt = min(a[p] - sum, rest[q]);
        sum += delt, rest[q] -= delt, ans += delt * (dep[q] - dep[p]);
        if (!rest[q]) choi[p]->erase(choi[p]->begin());
    }
    rest[p] = sum - a[p];
    if (rest[p]) choi[p]->emplace(dep[p], p);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) son[i].clear();
    for (int i = 2; i <= n; i++) cin >> fa[i], son[fa[i]].push_back(i);
    ans = dep[1] = 0;
    dfs(1);
    delete choi[1];

    cout << ans << endl;
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