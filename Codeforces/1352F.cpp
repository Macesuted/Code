/**
 * @file 1352F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-25
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
    int n0, n1, n2;
    cin >> n0 >> n1 >> n2;
    if (n1 == 0) {
        if (n0) {
            for (int i = 0; i <= n0; i++) cout << 0;
        } else {
            for (int i = 0; i <= n2; i++) cout << 1;
        }
        cout << endl;
        return;
    }
    if (!(n1 & 1)) cout << 1, n1--;
    for (int i = 0; i <= n0; i++) cout << 0;
    for (int i = 1; i < n1; i += 2) cout << 1 << 0;
    for (int i = 0; i <= n2; i++) cout << 1;
    cout << endl;
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
