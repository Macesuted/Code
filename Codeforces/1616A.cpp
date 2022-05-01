/**
 * @file 1616A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 105

int a[maxn * 2];

void solve(void) {
    int n;
    cin >> n;
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        a[t + maxn]++;
    }
    int ans = min(a[0 + maxn], 1);
    for (int i = 1; i <= 100; i++) ans += min(a[i + maxn] + a[-i + maxn], 2);
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
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
