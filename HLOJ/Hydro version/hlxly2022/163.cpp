/**
 * @file 163.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-18
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

int MaxTim;

typedef pair<int, int64_t> pil;

map<int, int64_t>* S[maxn];
vector<int> graph[maxn];
int d[maxn], w[maxn];

void dfs(int p) {
    S[p] = new map<int, int64_t>();
    for (auto i : graph[p]) {
        dfs(i);
        if (S[p]->size() < S[i]->size()) swap(S[p], S[i]);
        for (auto j : *S[i]) (*S[p])[j.first] += j.second;
    }
    if (d[p]) {
        (*S[p])[d[p]] += w[p];
        auto x = S[p]->upper_bound(d[p]);
        int64_t v = w[p];
        while (x != S[p]->end() && v >= x->second) v -= x->second, x = S[p]->erase(x);
        if (v) x->second -= v;
    }
    return;
}

void solve(void) {
    int n, m;
    cin >> n >> m >> MaxTim;
    for (int i = 2, x; i <= n; i++) cin >> x, graph[x].push_back(i);
    for (int i = 1, p, d_, w_; i <= m; i++) cin >> p >> d_ >> w_, d[p] = d_, w[p] = w_;
    dfs(1);
    int64_t sum = 0;
    for (auto i : *S[1]) sum += i.second;
    cout << sum << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
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