/**
 * @file 1981D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-01
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

#define maxn 1000005
#define maxv 300005

bool notPrime[maxv];
vector<int> prime, path;
vector<unordered_set<int>> graph;

void construct(int n) {
    graph.clear(), graph.resize(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++) graph[i].insert(j), graph[j].insert(i);
    if (n & 1) return;
    for (int i = 2; i < n; i += 2) graph[i].erase(i - 1), graph[i - 1].erase(i);
}
void dfs(int p) {
    while (!graph[p].empty()) {
        int q = *graph[p].begin();
        graph[p].erase(q), graph[q].erase(p);
        dfs(q);
    }
    path.push_back(p);
    return;
}

void solve(void) {
    int n;
    cin >> n;
    int l = 0, r = prime.size();
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        int64_t val = (int64_t)mid * (mid + 1) / 2 - ((mid & 1) ? 0 : mid / 2 - 1);
        (val < n - 1 ? l : r) = mid;
    }
    construct(r);
    path.clear(), dfs(r);
    for (int i = 0; i < n; i++) cout << prime[path[i] - 1] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxv; i++) {
        if (!notPrime[i]) prime.push_back(i);
        for (auto j = prime.begin(); j != prime.end() && i * *j < maxv; j++) {
            notPrime[i * *j] = true;
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}