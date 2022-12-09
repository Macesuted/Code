/**
 * @file 2067.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-09
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

int sg[20][20];

void solve(void) {
    int n, m, lg2 = 0, v2 = 1, lg3 = 0, v3 = 1, ans = 0;
    cin >> n >> m;
    while (v2 * 2 <= n) v2 *= 2, lg2++;
    while (v3 * 3 <= n) v3 *= 3, lg3++;
    for (int i = 0; i <= lg2; i++)
        for (int j = 0; j <= lg3; j++) {
            set<int> S;
            for (int p = 1, v = 0; p <= i; p++, v = 0)
                for (int q = 1; p * q <= i && q <= m; q++) S.insert(v ^= sg[i - p * q][j]);
            for (int p = 1, v = 0; p <= j; p++, v = 0)
                for (int q = 1; p * q <= j && q <= m; q++) S.insert(v ^= sg[i][j - p * q]);
            sg[i][j] = 0;
            while (S.count(sg[i][j])) sg[i][j]++;
        }
    for (int i = 1, v; i <= n; i++) {
        cin >> v;
        if (v == 1) continue;
        int t = i, x = 0, y = 0;
        while (t % 2 == 0) t /= 2, x++;
        while (t % 3 == 0) t /= 3, y++;
        ans ^= sg[x][y];
    }
    cout << (ans ? "win" : "lose") << endl;
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