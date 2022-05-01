/**
 * @file 1605C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 100005

int a[maxn];
bool vis[maxn];

void solve(void) {
    int n, m = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) vis[i] = false;
    for (int i = 1; i <= n; i++) {
        cin >> a[m + 1];
        if (a[m + 1] <= n && !vis[a[m + 1]])
            vis[a[m + 1]] = true;
        else
            m++;
    }
    sort(a + 1, a + m + 1);
    for (int i = 1, t = 1; i <= n; i++) {
        if (vis[i]) continue;
        if ((a[t] + 1) / 2 <= i) return cout << -1 << endl, void();
        t++;
    }
    cout << m << endl;
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
