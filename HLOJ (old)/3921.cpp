/**
 * @file extension.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

void solve(void) {
    int n;
    cin >> n;
    bool v = false, sup = false;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (i & 1)
            v ^= (x & 1);
        else {
            if ((x + 1) % (i + 1) == 0) sup ^= true;
            v ^= (x % (i + 1)) & 1;
        }
    }
    cout << ((v || sup) ? "tomato fish+1s" : "rainy day+1s") << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("extension.in", "r", stdin), freopen("extension.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
