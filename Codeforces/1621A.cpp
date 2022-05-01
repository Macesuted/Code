/**
 * @file 1621A.cpp
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
    int n, c;
    cin >> n >> c;
    if (n < c * 2 - 1)
        cout << -1 << endl;
    else {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j && (i & 1) && c)
                    c--, cout << 'R';
                else
                    cout << '.';
            }
            cout << endl;
        }
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
