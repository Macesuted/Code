/**
 * @file 13104.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-04
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

#define maxn 200005

typedef pair<int64_t, int> pli;
typedef tuple<int64_t, int, int> tlii;
typedef tuple<int64_t, int, int, int> tliii;

vector<int> a[maxn];
vector<int64_t> f[maxn];
int l[maxn], r[maxn];
pli id[maxn];

priority_queue<tlii, vector<tlii>, greater<tlii>> que;
priority_queue<tliii, vector<tliii>, greater<tliii>> S[maxn];

int64_t getF(int x, int p) {
    while ((int)f[x].size() <= p) {
        if (S[x].empty()) {
            f[x].push_back(-1);
            continue;
        }
        int64_t sum;
        int u, cntu, cntu1;
        tie(sum, u, cntu, cntu1) = S[x].top(), S[x].pop(), f[x].push_back(sum);
        if (cntu + 1 < cntu1) S[x].emplace(sum + a[x][cntu + 1] - a[x][cntu], u, cntu + 1, cntu1);
        if (u && u < cntu) S[x].emplace(sum + a[x][u] - a[x][u - 1], u - 1, u, cntu);
    }
    return f[x][p];
}

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1, c, x; i <= n; i++) cin >> c >> x, a[c].push_back(x);
    for (int i = 1; i <= m; i++) cin >> l[i] >> r[i], r[i] = min(r[i], (int)a[i].size()), sort(a[i].begin(), a[i].end());
    for (int i = 1; i <= m; i++) {
        int64_t sum = 0;
        if (l[i] == 0) f[i].push_back(0);
        for (int j = 1; j <= r[i]; j++) {
            sum += a[i][j - 1];
            if (j >= l[i]) S[i].emplace(sum, j - 1, j - 1, (int)a[i].size());
        }
    }
    int tm = 0;
    int64_t sum = 0;
    for (int i = 1; i <= m; i++) {
        if (!~getF(i, 0)) {
            for (int i = 1; i <= k; i++) cout << -1 << endl;
            return;
        }
        sum += getF(i, 0);
        if (~getF(i, 1)) id[++tm] = {getF(i, 1) - getF(i, 0), i};
    }
    sort(id + 1, id + tm + 1);
    cout << sum << endl;
    if (tm) que.emplace(sum + getF(id[1].second, 1) - getF(id[1].second, 0), 1, 1);
    for (int i = 1, p, fp; i < k; i++) {
        if (que.empty()) {
            cout << -1 << endl;
            continue;
        }
        tie(sum, p, fp) = que.top(), que.pop(), cout << sum << endl;
        int vp = id[p].second, vp1 = id[p + 1].second;
        if (~getF(vp, fp + 1)) que.emplace(sum + getF(vp, fp + 1) - getF(vp, fp), p, fp + 1);
        if (p < tm) que.emplace(sum + getF(vp1, 1) - getF(vp1, 0), p + 1, 1);
        if (fp == 1 && p < tm) que.emplace(sum + getF(vp, 0) - getF(vp, 1) + getF(vp1, 1) - getF(vp1, 0), p + 1, 1);
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("knapsack.in", "r", stdin), freopen("knapsack.out", "w", stdout);
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
