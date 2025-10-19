/**
 * @file 14609.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

int inter(int i, int j) {
    cout << i << ' ' << j << endl;
    int ret;
    cin >> ret;
    if (ret == 1) exit(0);
    return ret;
}

void solve(void) {
    int n, cur;
    cin >> n >> cur;

    for (int i = 2; i <= n; i++) {
        int mxv = cur, mxp = 0;
        for (int j = 1; j < n; j++) {
            int v = inter(i, +1);
            if (v > mxv) mxv = v, mxp = j;
        }
        cur = mxv, inter(i, 1 + mxp);
    }

    assert(cur == n);

    vector<bool> mark(n + 1, false);
    inter(1, +1), mark[1] = true;

    bool fnd = false;
    for (int i = 2; i <= n && !fnd; i++)
        for (int j = 1; j <= n && !fnd; j++)
            if (inter(i, +1) == n) inter(i, +1), mark[i] = fnd = true;

    assert(fnd);

    for (int t = 1; t <= n - 2; t++) {
        bool fnd = false;
        for (int i = 1; i <= n; i++) {
            if (mark[i]) continue;
            if (inter(i, +1) == n - t) {
                inter(i, t), mark[i] = fnd = true;
                break;
            }
            inter(i, -1);
        }
        assert(fnd);
    }

    assert(false);

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}