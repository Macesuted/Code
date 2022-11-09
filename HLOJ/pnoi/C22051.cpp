/**
 * @file C22051.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-07
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

typedef pair<int, int> pii;

int n, a[maxn];
vector<pii> graph[maxn];
int64_t f[maxn][2];
multiset<int64_t, greater<int64_t>> S;

bool check(int64_t lim, int p = 1, int fa = -1) {
    if (((int)graph[p].size() == 1 && ~fa) || graph[p].empty()) return f[p][0] = f[p][1] = 0, true;
    for (auto i : graph[p])
        if (i.first != fa && !check(lim, i.first, p)) return false;
    S.clear(), S.insert(0);
    for (int i = 0, x, d; i < (int)graph[p].size(); i++) {
        tie(x, d) = graph[p][i];
        if (x != fa) S.insert(min(f[x][0] + d, f[x][1] + max(0, d - a[x])));
        while (S.size() > 3) S.erase(--S.end());
    }
    f[p][0] = 1e18, f[p][1] = ((S.size() < 2 || *S.begin() + *(++S.begin()) <= lim) ? *S.begin() : 1e18);
    for (int i = 0; i < (int)graph[p].size(); i++) {
        int x = graph[p][i].first, d = graph[p][i].second;
        if (x == fa) continue;
        int64_t ov = min(f[x][0] + d, f[x][1] + max(0, d - a[x])),
                v = min(f[x][0] + max(0, d - a[p]), f[x][1] + max(0, d - a[x] - a[p]));
        bool flg = (S.find(ov) != S.end());
        if (flg) S.erase(S.find(ov));
        S.insert(v);
        if (S.size() < 2 || *S.begin() + *(++S.begin()) <= lim) f[p][0] = min(f[p][0], *S.begin());
        S.erase(S.find(v));
        if (flg) S.insert(ov);
    }
    return f[p][0] != 1e18;
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x, y, w; i < n; i++) cin >> x >> y >> w, graph[x].emplace_back(y, w), graph[y].emplace_back(x, w);
    int64_t l = -1, r = 2e10;
    while (l + 1 < r) {
        int64_t mid = l + ((r - l) >> 1);
        (check(mid) ? r : l) = mid;
    }
    cout << r << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("length.in", "r", stdin), freopen("length.out", "w", stdout);
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