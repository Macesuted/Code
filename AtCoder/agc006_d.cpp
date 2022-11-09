/**
 * @file agc006_d.cpp
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

#define maxn 200005

int a[maxn];
bool b[maxn];

int n, R;

bool check(int lim) {
    int cnt = 0, pl = n, pr = n;
    for (int i = 1; i <= R; i++) cnt += (b[i] = (a[i] >= lim));
    while (pl > 1 && b[pl] != b[pl - 1]) pl--;
    while (pr < R && b[pr] != b[pr + 1]) pr++;
    if (pl == 1 && pr == R) return 2 * cnt > R;
    return b[(n - pl < pr - n) ? pl : pr];
}

void solve(void) {
    cin >> n, R = 2 * n - 1;
    for (int i = 1; i <= R; i++) cin >> a[i];
    int l = 1, r = R + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (check(mid) ? l : r) = mid;
    }
    cout << l << endl;
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