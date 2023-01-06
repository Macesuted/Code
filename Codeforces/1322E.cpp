/**
 * @file 1322E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 500005

typedef pair<int, int> pii;

int n, a[maxn], ans2[maxn];
bool v[maxn];
map<int, vector<int>> rec;
set<int> S, rest;

void update(int x) {
    (x > 1 && v[x - 1] != v[x]) ? (S.erase(x), void()) : (S.insert(x), void());
    (x < n && v[x] != v[x + 1]) ? (S.erase(x + 1), void()) : (S.insert(x + 1), void());
    return;
}
void mark(int l, int r, int v) {
    for (auto i = rest.lower_bound(l); i != rest.end() && *i <= r; i = rest.erase(i)) ans2[*i] = v;
    return;
}
pii query(int x) { return {*--S.upper_bound(x), *S.upper_bound(x) - 1}; }

void solve(void) {
    cin >> n;
    S.insert(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i], v[i] = true, rec[a[i]].push_back(i), S.insert(i), rest.insert(i);
    int ans1 = 0;
    for (auto &i : rec) {
        for (auto j : i.second) v[j] = false;
        for (auto j : i.second) update(j);
        auto calc = [&](int p) {
            auto [l, r] = query(p);
            ans1 = max(ans1, r - l + 1);
            if (!((r - l + 1) & 1))
                if (!v[l])
                    mark(l, (l + r) / 2, i.first);
                else
                    mark((l + r) / 2 + 1, r, i.first);
            else if (!v[l])
                mark(l, r, i.first);
        };
        for (auto j : i.second) {
            if (j > 1) calc(j - 1);
            calc(j);
            if (j < n) calc(j + 1);
        }
    }
    cout << (ans1 - 1) / 2 << endl;
    for (int i = 1; i <= n; i++) cout << ans2[i] << ' ';
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