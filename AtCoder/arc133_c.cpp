/**
 * @file arc133_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

void solve(void) {
    int h, w, k;
    cin >> h >> w >> k;
    long long sumx = 0, sumy = 0;
    for (int i = 1; i <= h; i++) {
        int x;
        cin >> x;
        sumx += (1LL * (k - 1) * w + k - x) % k;
    }
    for (int i = 1; i <= w; i++) {
        int x;
        cin >> x;
        sumy += (1LL * (k - 1) * h + k - x) % k;
    }
    if (abs(sumx - sumy) % k != 0)
        cout << -1 << endl;
    else
        cout << 1LL * h * w * (k - 1) - max(sumx, sumy) << endl;
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
