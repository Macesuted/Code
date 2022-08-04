/**
 * @file 1023B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-09
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool mem1;

void solve(void) {
    long long n, k;
    cin >> n >> k;
    long long l = max(1LL, k - n), r = (k - 1) / 2;
    cout << max(0LL, r - l + 1) << endl;
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
