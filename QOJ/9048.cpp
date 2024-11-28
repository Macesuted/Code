/**
 * @file 9048.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-20
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
#define maxm 100005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int a[maxn], lim[maxn][maxn], fu[maxn][maxn], fd[maxn][maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<tiii> itrv;
    for (int i = 1, p, d, t; i <= m; i++) {
        cin >> p >> d >> t;
        int l = ((d - p - a[p]) % n + n) % n, len = 2 * a[p];
        if (len < n - 1) itrv.emplace_back(t, l, len);
    }
    sort(itrv.begin(), itrv.end());

    for (int i = 0; i < n; i++) {
        lim[i][0] = 0, fu[i][0] = fd[i][0] = -1;
        for (int j = 1; j < n; j++) lim[i][j] = INT_MAX, fu[i][j] = fd[i][j] = -1;
    }

    for (int i = 0; i < n; i++) fu[i][n - 1] = fd[i][n - 1] = INT_MAX;

    for (int l = 0; l < n; l++) {
        vector<pii> rec(1, {0, 0});
        for (auto [t, tl, tlen] : itrv)
            if (!((tl <= l && l <= tl + tlen) || (l < tl && l <= tl + tlen - n))) {
                int len = (tl - l + n) % n;
                if (rec.back().first < len) rec.emplace_back(len, t);
            }

        for (int i = 1; i < (int)rec.size(); i++)
            for (int len = rec[i - 1].first; len < rec[i].first; len++) lim[l][len] = rec[i].second - 1;
    }

    for (int len = n - 1; len; len--)
        for (int l = 0; l < n; l++) {
            int nl = (l == n - 1 ? 0 : l + 1);

            fu[l][len] = min(fu[l][len], lim[l][len]);
            fd[l][len] = min(fd[l][len], lim[l][len]);
            fu[l][len] = max(fu[l][len], fd[l][len] - len);
            fd[l][len] = max(fd[l][len], fu[l][len] - len);

            fd[nl][len - 1] = max(fd[nl][len - 1], fd[l][len] - 1);
            fu[l][len - 1] = max(fu[l][len - 1], fu[l][len] - 1);
        }

    auto ans = [&](int p) { return max(fu[p][0], fd[p][0]) != -1; };

    cout << ans(0);
    for (int i = n - 1; i; i--) cout << ans(i);
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}