/**
 * @file abc227_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool mem1;

void solve(void) {
    int n, k, a;
    cin >> n >> k >> a;
    k %= n;
    a = (a - 1 + k - 1) % n + 1;
    cout << a << endl;
    return;
}

bool mem2;

int main() {
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
