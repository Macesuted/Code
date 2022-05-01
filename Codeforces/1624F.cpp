/**
 * @file 1624F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

int ask(int p) {
    cout << "+ " << p << endl;
    int ret;
    cin >> ret;
    return ret;
}
int near(int v, int d) {
    int p = v / d * d;
    if (p < v) p += d;
    return p;
}

void solve(void) {
    int n;
    cin >> n;
    int l = 1, r = n - 1, vd = 0;
    while (l < r) {
        int mid = (l + r + 1) >> 1, v = near(mid + vd, n), ret = ask(v - vd - mid);
        vd = v - mid;
        if (ret == v / n)
            l = mid;
        else
            r = mid - 1;
    }
    cout << "! " << l + vd << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
