/**
 * @file 1738C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-30
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

#define maxn 105

int a[maxn];
bool sg[maxn][maxn][2];

void solve(void) {
    int n, ocnt = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], ocnt += (a[i] & 1);
    cout << (sg[ocnt][n - ocnt][0] ? "Alice" : "Bob") << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    sg[0][0][0] = true, sg[0][0][1] = false;
    for (int i = 0; i < maxn; i++)
        for (int j = (i == 0); j < maxn; j++)
            for (int k = 0; k < 2; k++)
                sg[i][j][k] = ((i ? !sg[i - 1][j][!(((i - 1) & 1) ^ (!k))] : false) ||
                               (j ? !sg[i][j - 1][!((i & 1) ^ k)] : false));
    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}