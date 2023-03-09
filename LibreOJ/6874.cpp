/**
 * @file 6874.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 400005
#define mod 998244353

typedef pair<int64_t, int64_t> pII;

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

int64_t f[maxn];

void solve(void) {
    int n;
    cin >> n;
    int64_t v = Pow(n + 2, mod - 2);
    for (int i = 0; i <= n; i++) cout << (1 + (i == 0)) * v % mod << ' ';
    cout << endl;
    int64_t sum = 3, pw2 = 1;
    f[0] = 1, f[1] = 2;
    for (int i = 2; i <= n; i++) sum = (sum + (f[i] = pw2 * (i + 3) % mod)) % mod, pw2 = pw2 * 2 % mod;
    sum = Pow(sum, mod - 2);
    for (int i = 0; i <= n; i++) cout << f[i] * sum % mod << ' ';
    cout << endl;
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