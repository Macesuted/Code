/**
 * @file abc227_c.cpp
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
    long long n, ans = 0;
    cin >> n;
    for (long long i = 1; i * i * i <= n; i++)
        for (long long j = i; i * j * j <= n; j++)
            ans += n / (i * j) - j + 1;
    cout << ans << endl;
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
