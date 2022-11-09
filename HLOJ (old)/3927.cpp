/**
 * @file 3927.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 15
#define maxk 100005
#define maxq 200005

typedef pair<int, int> pii;

bitset<1 << maxn> s[maxq / 2 + 50];
int a[maxn + 1][maxk], ans[maxq];
pii qwq[maxk][maxn];

void solve(void) {
    int k, n, q;
    cin >> k >> n >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++) cin >> a[i][j];
    for (int i = 0; i < n; i++)
        for (int S = 0; S < (1 << n); S++) s[i + 1][S] = S >> i & 1;
    for (int j = 1; j <= k; j++) {
        vector<pii> cac;
        for (int i = 1; i <= n; i++) cac.emplace_back(a[i][j], i - 1);
        sort(cac.begin(), cac.end());
        int S = (1 << n) - 1;
        for (int i = 0; i < n; i++) qwq[j][i] = {S, cac[i].first}, S ^= 1 << cac[i].second;
    }
    for (int i = 1, cnt = n; i <= q; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 3) {
            int ans = 0;
            for (int i = 0; i < n; i++)
                if (s[x][qwq[y][i].first]) ans = max(ans, qwq[y][i].second);
            cout << ans << endl;
        } else
            s[++cnt] = (op == 1) ? (s[x] | s[y]) : (s[x] & s[y]);
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("fall.in", "r", stdin), freopen("fall.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
