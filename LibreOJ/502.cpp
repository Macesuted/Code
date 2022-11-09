/**
 * @file 502.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-09
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

#define maxn 1000005
#define maxm 2000005

typedef pair<uint64_t, int> pUi;

uint64_t a[maxn], pow3[41], pre[maxm];
pUi rec[maxm];

uint64_t Xor3(uint64_t x, uint64_t y) {
    uint64_t ans = 0;
    for (int i = 0; i < 40; i++) ans += (x % 3 + y % 3) % 3 * pow3[i], x /= 3, y /= 3;
    return ans;
}

void solve(void) {
    int n, m, lastans = 0;
    cin >> n >> m;
    mt19937_64 rnd(114514);
    for (int i = 1; i <= n; i++) a[i] = rnd() % pow3[40], rec[i] = {a[i], i}, rec[i + n] = {Xor3(a[i], a[i]), i};
    sort(rec + 1, rec + 2 * n + 1);
    for (int i = 1; i <= m; i++) {
        int u, p;
        cin >> u >> p, u ^= lastans, p ^= lastans;
        pre[i] = Xor3(pre[p], a[u]);
        if (!pre[i])
            cout << (lastans = -1) << endl;
        else {
            int p = lower_bound(rec + 1, rec + 2 * n + 1, pUi{pre[i], 0}) - rec;
            if (p == 2 * n + 1 || rec[p].first != pre[i])
                cout << (lastans = -2) << endl;
            else
                cout << (lastans = rec[p].second) << endl;
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

    pow3[0] = 1;
    for (int i = 1; i < 41; i++) pow3[i] = pow3[i - 1] * 3;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}