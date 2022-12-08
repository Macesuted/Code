/**
 * @file 2703.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-08
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

int n, a[2][maxn], f[2][10][2];
vector<int> v[2];

int solve(int a[]) {
    v[1].clear(), memset(f[1], 0x3f, sizeof(f[1]));
    for (int i = 1; i <= min(n, 3); i++) {
        if (a[i] >= a[1]) v[1].push_back(a[i]);
        if (a[i] + 1 >= a[1]) v[1].push_back(a[i] + 1);
    }
    sort(v[1].begin(), v[1].end());
    for (int i = 0; i < (int)v[1].size(); i++) f[1][i][0] = v[1][i] - a[1];
    for (int i = 2; i <= n; i++) {
        bool t = i & 1;
        v[t].clear(), memset(f[t], 0x3f, sizeof(f[t]));
        for (int j = max(1, i - 2); j <= min(n, i + 2); j++) {
            if (a[j] >= a[i]) v[t].push_back(a[j]);
            if (a[j] + 1 >= a[i]) v[t].push_back(a[j] + 1);
        }
        sort(v[t].begin(), v[t].end());
        int tx = v[!t].size(), ty = v[t].size();
        for (int j = ty - 1, k = tx - 1, val = 0x3f3f3f3f; ~j; j--) {
            while (~k && v[!t][k] > v[t][j]) val = min(val, f[!t][k--][1]);
            f[t][j][0] = val;
            if (~k && v[!t][k] == v[t][j]) f[t][j][0] = min(f[t][j][0], f[!t][k][0]);
            f[t][j][0] = min(0x3f3f3f3f, f[t][j][0] + v[t][j] - a[i]);
        }
        for (int j = 0, k = 0, val = 0x3f3f3f3f; j < ty; j++) {
            while (k < tx && v[!t][k] < v[t][j]) val = min(val, f[!t][k++][0]);
            f[t][j][1] = val;
            if (k < tx && v[!t][k] == v[t][j]) f[t][j][1] = min(f[t][j][1], f[!t][k][1]);
            f[t][j][1] = min(0x3f3f3f3f, f[t][j][1] + v[t][j] - a[i]);
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < 10; i++) ans = min(ans, f[n & 1][i][0]);
    return ans;
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[0][i] >> a[1][i], a[0][i] = 1e6 - a[0][i];
    cout << solve(a[0]) + solve(a[1]) << endl;
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