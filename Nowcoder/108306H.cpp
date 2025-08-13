/**
 * @file 108306H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 100005

const int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int pre[3000], a[maxn], f[maxn][3], dl[maxn], dr[maxn];

bool leap(int Y) { return Y % 4 == 0 && (Y % 400 == 0 || Y % 100 != 0); }

void solve(void) {
    pre[2000] = 0;
    for (int i = 2000; i <= 2999; i++) pre[i + 1] = pre[i] + 365 + leap(i);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string S, T;
        cin >> S >> T;

        int Y = stoi(S.substr(0, 4)), M = stoi(S.substr(5, 2)), D = stoi(S.substr(8, 2));
        int h = stoi(T.substr(0, 2)), m = stoi(T.substr(3, 2)), s = stoi(T.substr(6, 2));

        a[i] = pre[Y] + D;
        for (int t = 1; t < M; t++) a[i] += day[t] + (t == 2 && leap(Y));

        dl[i] = dr[i] = 0;
        if (h < 20) dl[i] = -1;
        if (h >= 18) dr[i] = +1;
    }

    int ans = 1;

    for (int i = 1; i <= n; i++) f[i][0] = f[i][1] = f[i][2] = -1e9;
    for (int i = dl[1]; i <= dr[1]; i++) f[1][i + 1] = 1;
    for (int i = 2; i <= n; i++)
        for (int d1 = dl[i - 1]; d1 <= dr[i - 1]; d1++)
            for (int d2 = dl[i]; d2 <= dr[i]; d2++) {
                int x = a[i - 1] + d1, y = a[i] + d2;
                if (x > y) continue;
                if (x == y) f[i][d2 + 1] = max(f[i][d2 + 1], f[i - 1][d1 + 1]);
                if (x + 1 == y) f[i][d2 + 1] = max(f[i][d2 + 1], f[i - 1][d1 + 1] + 1);
                if (x + 1 < y) f[i][d2 + 1] = max(f[i][d2 + 1], 1);
                ans = max(ans, f[i][d2 + 1]);
            }

    cout << ans << ' ';

    auto chk = [&](int lim) -> bool {
        for (int i = 1; i <= n; i++) f[i][0] = f[i][1] = f[i][2] = 1e9;
        for (int i = dl[1]; i <= dr[1]; i++) f[1][i + 1] = 1;
        for (int i = 2; i <= n; i++)
            for (int d1 = dl[i - 1]; d1 <= dr[i - 1]; d1++)
                for (int d2 = dl[i]; d2 <= dr[i]; d2++) {
                    int x = a[i - 1] + d1, y = a[i] + d2;
                    if (x > y || f[i - 1][d1 + 1] > lim) continue;
                    if (x == y) f[i][d2 + 1] = min(f[i][d2 + 1], f[i - 1][d1 + 1]);
                    if (x + 1 == y && f[i - 1][d1 + 1] < lim) f[i][d2 + 1] = min(f[i][d2 + 1], f[i - 1][d1 + 1] + 1);
                    if (x + 1 < y) f[i][d2 + 1] = min(f[i][d2 + 1], 1);
                }

        return min({f[n][0], f[n][1], f[n][2]}) <= lim;
    };

    int l = 0, r = n;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (chk(mid) ? r : l) = mid;
    }

    cout << r << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}