/**
 * @file 102428L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1005

string a[maxn];
int sum[maxn][maxn], f[maxn];
int n, m;

int getSum(int xl, int xr, int yl, int yr) { return sum[xr][yr] - sum[xl - 1][yr] - sum[xr][yl - 1] + sum[xl - 1][yl - 1]; }

bool check(int len) {
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++)
        for (int l = 1, r = len; r <= m; l++, r++) {
            if (getSum(i, i, l, r) == 0 || getSum(i, i, l, r) == r - l + 1)
                f[l]++;
            else
                f[l] = 0;
            if (f[l] == len) return true;
        }
    return false;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> a[i], a[i] = ' ' + a[i];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) sum[i][j] = sum[i][j - 1] + (a[i][j] == 'G');

    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++) sum[i][j] += sum[i - 1][j];

    int l = 1, r = max(n, m) + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (check(mid) ? l : r) = mid;
    }

    cout << l * l << endl;

    return 0;
}