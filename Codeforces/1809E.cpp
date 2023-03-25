/**
 * @file 1809E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005
#define maxv 1005

int a[maxn], ans[maxv][maxv], lf[maxn], rf[maxn];

void solve(void) {
    int n, A, B;
    cin >> n >> A >> B;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int c = 0; c <= A + B; c++) {
        int L = max(0, c - B), R = min(A, c), l = L, r = R, tl = L, tr = R;
        for (int i = 1; i <= n; i++) {
            l -= a[i], r -= a[i];
            if (r < L) l = r = L, tl = tr + 1;
            if (l > R) l = r = R, tl = tr + 1;
            if (l < L) tl += L - l, l = L;
            if (r > R) tr -= r - R, r = R;
        }
        for (int i = L; i <= R; i++) ans[i][c - i] = (tl > tr ? l : min(max(i, tl), tr) - tl + l);
    }
    for (int i = 0; i <= A; i++) {
        for (int j = 0; j <= B; j++) cout << ans[i][j] << ' ';
        cout << endl;
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