/**
 * @file 1623C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 200005

long long a[maxn], b[maxn];
int n;

bool check(int lim) {
    for (int i = 1; i <= n; i++) b[i] = 0;
    for (int i = n; i >= 3; i--) {
        long long p = max(0LL, min(a[i], a[i] + b[i] - lim) / 3);
        b[i] -= 3 * p, b[i - 1] += p, b[i - 2] += 2 * p;
    }
    for (int i = 1; i <= n; i++)
        if (a[i] + b[i] < lim) return false;
    return true;
}

void solve(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    long long l = 1, r = 1e9 + 5;
    while (l + 1 < r) {
        long long mid = (l + r) >> 1;
        check(mid) ? l = mid : r = mid;
    }
    cout << l << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
