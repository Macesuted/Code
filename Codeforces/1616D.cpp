/**
 * @file 1616D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 500005

int a[maxn];

void solve(void) {
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> x;
    int ans = n;
    for (int i = 1, sum = 0, len = 0; i <= n; i++)
        if ((a[i] < x * (len + 1) - sum) && len != 0)
            ans--, sum = 0, len = 0;
        else {
            sum += a[i], len++;
            if (x * 2 - a[i] > x * (len + 1) - sum) sum = a[i], len = 1;
        }
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
