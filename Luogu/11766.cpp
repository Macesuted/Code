/**
 * @file 11766.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005

using pii = pair<int, int>;
using tlil = tuple<int64_t, int, int64_t>;

vector<pii> graph[maxn];
tlil f[maxn];

int64_t ans = 0;
void dfs1(int p, int pre = -1) {
    f[p] = {0, 1, 1};
    for (auto [q, w] : graph[p])
        if (q != pre) {
            dfs1(q, p);

            tlil fq = {get<0>(f[q]) + w, get<1>(f[q]), get<1>(f[q]) + get<2>(f[q])};

            if (get<0>(fq) > get<0>(f[p]))
                f[p] = fq;
            else if (get<0>(fq) == get<0>(f[p]))
                get<1>(f[p]) += get<1>(fq), get<2>(f[p]) += get<2>(fq);
        }

    return;
}
void dfs2(int p, int pre = -1) {
    tlil fp1 = {0, 1, 1}, fp2 = {0, 1, 1};

    for (auto [q, w] : graph[p]) {
        tlil fq = {get<0>(f[q]) + w, get<1>(f[q]), get<1>(f[q]) + get<2>(f[q])};
        if (get<0>(fq) > get<0>(fp1))
            fp2 = fp1, fp1 = fq;
        else if (get<0>(fq) == get<0>(fp1))
            get<1>(fp1) += get<1>(fq), get<2>(fp1) += get<2>(fq);
        else if (get<0>(fq) > get<0>(fp2))
            fp2 = fq;
        else if (get<0>(fq) == get<0>(fp2))
            get<1>(fp2) += get<1>(fq), get<2>(fp2) += get<2>(fq);
    }

    ans += get<2>(fp1);

    for (auto [q, w] : graph[p])
        if (q != pre) {
            tlil fq = {get<0>(f[q]) + w, get<1>(f[q]), get<1>(f[q]) + get<2>(f[q])};
            f[p] = fp1;
            if (get<0>(f[p]) == get<0>(fq)) get<1>(f[p]) -= get<1>(fq), get<2>(f[p]) -= get<2>(fq);
            if (!get<1>(f[p])) f[p] = fp2;
            dfs2(q, p);
        }

    return;
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x, y, w; i < n; i++) cin >> x >> y >> w, graph[x].emplace_back(y, w), graph[y].emplace_back(x, w);

    dfs1(1);
    dfs2(1);

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