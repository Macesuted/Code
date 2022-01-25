/**
 * @file 1352E.cpp
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

#define maxn 8005

int a[maxn];
bool vis[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], vis[i] = false;
    for (int l = 1; l < n; l++) {
        int sum = a[l] + a[l + 1];
        for (int r = l + 1; r <= n && sum <= n; sum += a[++r]) vis[sum] = true;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (vis[a[i]]) cnt++;
    cout << cnt << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
