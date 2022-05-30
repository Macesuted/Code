/**
 * @file 2074.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005
#define maxlgn 20

int a[maxn], maxVal[maxlgn][maxn], lg[maxn];

int getMax(int l, int r) {
    int x = lg[r - l + 1];
    return max(maxVal[x][l], maxVal[x][r - (1 << x) + 1]);
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], maxVal[0][i] = a[i];
    for (int i = 1; i <= n; i++) {
        lg[i] = lg[i - 1];
        if (1 << (lg[i] + 1) <= i) lg[i]++;
    }
    for (int i = 1; i < maxlgn; i++)
        for (int j = 1; j <= n; j++) maxVal[i][j] = max(maxVal[i - 1][j], maxVal[i - 1][min(n, j + (1 << (i - 1)))]);
    for (int i = 1; i <= n; i++) {
        int ans = 0;
        for (int v = 1; i - (v - 1) * (v - 1) - 1 >= 1; v++)
            ans = max(ans, getMax(max(1, i - v * v), i - (v - 1) * (v - 1) - 1) + v);
        for (int v = 1; i + (v - 1) * (v - 1) + 1 <= n; v++)
            ans = max(ans, getMax(i + (v - 1) * (v - 1) + 1, min(n, i + v * v)) + v);
        cout << max(0, ans - a[i]) << endl;
    }
    return;
}

bool mem2;

int main() {
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