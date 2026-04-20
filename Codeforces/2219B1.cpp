/**
 * @file 2219B1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 2005

int pa[maxn];

int get(int l, int r) {
    cout << "? " << r - l + 1;
    for (int i = l; i <= r; i++) cout << ' ' << pa[i];
    cout << endl;

    int t;
    cin >> t;

    return t;
}

int query(int s, int n) {
    int l = s - 1, r = n;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (((get(1, mid) ^ mid) & 1) ? r : l) = mid;
    }

    return r;
}

void solve(void) {
    int n;
    cin >> n, n = 2 * n + 1;
    for (int i = 1; i <= n; i++) pa[i] = i;

    int ret = query(1, n);
    swap(pa[1], pa[ret]);
    ret = query(2, n);
    swap(pa[2], pa[ret]);
    ret = query(3, n);
    swap(pa[3], pa[ret]);

    cout << "! " << pa[1] << ' ' << pa[2] << ' ' << pa[3] << endl;

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
