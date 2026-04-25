/**
 * @file 1535E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 300005
#define maxlgn 20

int fa[maxn][maxlgn], v[maxn], s[maxn];

void solve(void) {
    int q;
    cin >> q >> s[0] >> v[0];

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;

        if (op == 1) {
            cin >> fa[i][0] >> s[i] >> v[i];

            for (int j = 1; j < maxlgn; j++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
        } else {
            int q, cnt = 0, rest;
            cin >> q >> rest;

            int64_t ans = 0;
            while (rest && s[q]) {
                int p = q;
                for (int i = maxlgn - 1; ~i; i--)
                    if (s[fa[p][i]]) p = fa[p][i];
                int cv = min(s[p], rest);
                s[p] -= cv, cnt += cv, rest -= cv, ans += (int64_t)cv * v[p];
            }

            cout << cnt << ' ' << ans << endl;
        }
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
