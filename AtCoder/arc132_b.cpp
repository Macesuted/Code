/**
 * @file arc132_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 100005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int p = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] == n) p = i;
    if (a[p % n + 1] == a[p] - 1)
        cout << min(p - 1 + 1, 1 + n - p + 1) << endl;
    else
        cout << (p == n ? 0 : min(p, 1 + n - p + 1)) << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
