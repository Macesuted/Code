/**
 * @file 1632C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-30
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
    int a, b;
    cin >> a >> b;
    int ans = b - a;
    for (int c = b; c < b + ans; c++) {
        int d = 0;
        for (int i = 30; ~i; i--)
            if ((c >> i & 1) && d + (1 << i) < a)
                d += 1 << i;
        int p = 0;
        for (int i = 0; i <= 30; i++)
            if ((c >> i & 1) && !(d >> i & 1)) {
                p = i;
                break;
            }
        d += 1 << p;
        for (int i = 0; i < p; i++)
            if ((c >> i & 1)) d -= 1 << i;
        ans = min(ans, c - b + 1 + d - a);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
