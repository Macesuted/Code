/**
 * @file abc227_d.cpp
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

#define maxn 200005

long long a[maxn];
int n, k;

bool check(__int128_t lim) {
    __int128_t sum = 0;
    for (int i = 1; i <= n; i++) sum += min(lim, (__int128_t)a[i]);
    return sum >= k * lim;
}

void solve(void) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    long long l = 0, r = 1e18 / k;
    while (l + 1 < r) {
        long long mid = (l + r) >> 1;
        check(mid) ? l = mid : r = mid;
    }
    cout << l << endl;
    return;
}

bool mem2;

int main() {
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
