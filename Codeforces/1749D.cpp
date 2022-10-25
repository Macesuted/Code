/**
 * @file 1749D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-20
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

#define maxn 300005
#define mod 998244353

bool notp[maxn];
vector<int> prime;

void solve(void) {
    notp[1] = true;
    for (int i = 2; i < maxn; i++) {
        if (!notp[i]) prime.push_back(i);
        for (auto j = prime.begin(); i * *j < maxn; j++) {
            notp[i * *j] = true;
            if (i % *j == 0) break;
        }
    }
    int64_t n, m;
    cin >> n >> m;
    int64_t tot = 0, mulm = 1, ans = 1, mul = 1;
    for (int i = 1; i <= n; i++) {
        if (mul <= m && !notp[i]) mul *= i;
        ans = (m / mul) % mod * ans % mod;
        mulm = m % mod * mulm % mod, tot = (tot + mulm + mod - ans) % mod;
    }
    cout << tot << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}