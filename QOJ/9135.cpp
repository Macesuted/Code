/**
 * @file 9135.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-09-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 505

typedef pair<int, int> pii;
typedef pair<int64_t, int> pli;

int64_t a[maxn], f[maxn][maxn];
vector<pii> graph[maxn];
bool vis[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int len = 2; len <= n; len++) {
        priority_queue<pli, vector<pli>, greater<pli>> que;
        for (int i = 1; i <= n; i++) graph[i].clear(), vis[i] = false;

        for (int l = 1, r = len; r <= n; l++, r++) {
            f[l][r] = 1e18;
            for (int c = 1; c <= n; c++) {
                int clen = min(c - 1, n - c), cl = c - clen, cr = c + clen;

                auto rev = [&](int p) { return p + (c - p) * 2; };

                int pl = rev(r), pr = rev(l);
                if (1 <= pl && pr <= n) graph[pl].emplace_back(l, a[c]);

                if (cl == 1) {
                    if (cr >= r || cr < l) continue;
                    f[l][r] = min(f[l][r], max(f[rev(cr)][rev(l)], f[cr + 1][r]) + a[c]);
                } else {
                    if (cl <= l || cl > r) continue;
                    f[l][r] = min(f[l][r], max(f[rev(r)][rev(cl)], f[l][cl - 1]) + a[c]);
                }
            }
            que.emplace(f[l][r], l);
        }
        while (!que.empty()) {
            int p = que.top().second;
            que.pop();
            if (vis[p]) continue;
            vis[p] = true;
            for (auto [i, d] : graph[p])
                if (f[i][i + len - 1] > f[p][p + len - 1] + d) que.emplace(f[i][i + len - 1] = f[p][p + len - 1] + d, i);
        }
    }

    cout << f[1][n] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
