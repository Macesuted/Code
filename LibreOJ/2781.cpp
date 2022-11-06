/**
 * @file 2781.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-06
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

#define maxn 2005

typedef tuple<int, int, int> tiii;

int lim[5][5], fa[maxn];
tiii a[maxn];
vector<tiii> edges;

int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }
int Min(int &a, int b) { return a = min(a, b); }

void solve(void) {
    int n, m, w, h;
    cin >> n >> m >> w >> h;
    for (int i = 1; i <= n; i++) cin >> get<0>(a[i]) >> get<1>(a[i]) >> get<2>(a[i]);
    auto dist = [](tiii a, tiii b) {
        auto sqr = [](long double x) { return x * x; };
        return int(sqrt(sqr(get<0>(a) - get<0>(b)) + sqr(get<1>(a) - get<1>(b))) - get<2>(a) - get<2>(b));
    };
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) edges.emplace_back(dist(a[i], a[j]), i, j);
    for (int i = 1; i <= n; i++) edges.emplace_back(get<1>(a[i]) - get<2>(a[i]), n + 1, i);
    for (int i = 1; i <= n; i++) edges.emplace_back(w - get<0>(a[i]) - get<2>(a[i]), n + 2, i);
    for (int i = 1; i <= n; i++) edges.emplace_back(h - get<1>(a[i]) - get<2>(a[i]), n + 3, i);
    for (int i = 1; i <= n; i++) edges.emplace_back(get<0>(a[i]) - get<2>(a[i]), n + 4, i);
    for (int i = 1; i <= n + 4; i++) fa[i] = i;
    sort(edges.begin(), edges.end()), memset(lim, 0x3f, sizeof(lim));
    for (auto i : edges) {
        int w = get<0>(i) / 2;
        fa[getfa(get<1>(i))] = getfa(get<2>(i));
        if (getfa(n + 1) == getfa(n + 2))
            Min(lim[1][2], w), Min(lim[2][1], w), Min(lim[2][3], w), Min(lim[2][4], w), Min(lim[3][2], w), Min(lim[4][2], w);
        if (getfa(n + 1) == getfa(n + 3))
            Min(lim[1][2], w), Min(lim[1][3], w), Min(lim[2][1], w), Min(lim[2][4], w), Min(lim[3][1], w), Min(lim[3][4], w),
                Min(lim[4][2], w), Min(lim[4][3], w);
        if (getfa(n + 1) == getfa(n + 4))
            Min(lim[1][2], w), Min(lim[1][3], w), Min(lim[1][4], w), Min(lim[2][1], w), Min(lim[3][1], w), Min(lim[4][1], w);
        if (getfa(n + 2) == getfa(n + 3))
            Min(lim[1][3], w), Min(lim[2][3], w), Min(lim[3][1], w), Min(lim[3][2], w), Min(lim[3][4], w), Min(lim[4][3], w);
        if (getfa(n + 2) == getfa(n + 4))
            Min(lim[1][3], w), Min(lim[1][4], w), Min(lim[2][3], w), Min(lim[2][4], w), Min(lim[3][1], w), Min(lim[3][2], w),
                Min(lim[4][1], w), Min(lim[4][2], w);
        if (getfa(n + 3) == getfa(n + 4))
            Min(lim[1][4], w), Min(lim[2][4], w), Min(lim[3][4], w), Min(lim[4][1], w), Min(lim[4][2], w), Min(lim[4][3], w);
    }
    while (m--) {
        int r, e;
        cin >> r >> e;
        for (int i = 1; i <= 4; i++)
            if (lim[e][i] >= r) cout << i;
        cout << endl;
    }
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