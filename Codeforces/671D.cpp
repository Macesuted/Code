/**
 * @file 671D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-10
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

#define maxn 300005

typedef pair<int, int64_t> pil;

vector<int> graph[maxn];
vector<pil> chain[maxn];
set<pil>* S[maxn];
int dep[maxn];
int64_t base[maxn], lazy[maxn];

void insert(int a, pil b) {
    auto p = S[a]->lower_bound({b.first, INT64_MIN});
    if (p != S[a]->end()) {
        if (p->second <= b.second) return;
        if (p->first == b.first) S[a]->erase(p);
    }
    p = S[a]->insert(b).first;
    while (p != S[a]->begin() && (--p)->second >= b.second) p = S[a]->erase(p);
    return;
}
void merge(int lim, int a, int b) {
    if (S[a]->size() < S[b]->size()) swap(S[a], S[b]), swap(lazy[a], lazy[b]);
    for (auto i : *S[b])
        if (-i.first < lim) insert(a, {i.first, i.second + lazy[b] - lazy[a]});
    return S[b]->clear();
}

void dfs(int p, int pre = 0) {
    dep[p] = dep[pre] + 1, S[p] = new set<pil>;
    int64_t tot = 0;
    for (auto i : graph[p])
        if (i != pre) dfs(i, p), tot += base[i], lazy[i] -= base[i], merge(dep[p], p, i);
    lazy[p] += tot;
    for (auto i : chain[p]) insert(p, {-dep[i.first], i.second - lazy[p] + tot});
    while (!S[p]->empty() && -S[p]->begin()->first >= dep[p]) S[p]->erase(S[p]->begin());
    if (S[p]->empty() && p != 1) cout << -1 << endl, exit(0);
    base[p] = S[p]->begin()->second + lazy[p];
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1, x, y; i < n; i++) cin >> x >> y, graph[x].push_back(y), graph[y].push_back(x);
    for (int i = 1, u, v, c; i <= m; i++) cin >> u >> v >> c, chain[u].emplace_back(v, c);
    dfs(1);
    int64_t ans = 0;
    for (auto i : graph[1]) ans += base[i];
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}