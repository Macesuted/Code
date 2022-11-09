/**
 * @file C22057.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

void solve(void) {
    int64_t n;
    cin >> n;
    if (n & 1) {
        int p = 1;
        while (n % prime[p] == 0) p++;
        cout << n * prime[p] << ' ' << n * (prime[p] - 1) << endl;
    } else
        cout << 2 * n << ' ' << n << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("Z.in", "r", stdin), freopen("Z.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}