/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 4000005

typedef pair<int, int> pii;

int f[maxn], p[maxn];

void work(void) {
    int n, mod;
    cin >> n >> mod;
    int pre = f[1] = 1;
    for (register int j = 2; j <= n; j++) {
        p[j] = (p[j] + 1) % mod;
        if (j + j <= n) p[j + j] = (p[j + j] - f[1] + mod) % mod;
    }
    for (register int i = 2; i <= n; i++) {
        pre = (pre + p[i]) % mod;
        f[i] = (f[i] + pre) % mod;
        for (register int j = 2; i * j <= n; j++) {
            p[i * j] = (p[i * j] + f[i]) % mod;
            if (i * j + j <= n) p[i * j + j] = (p[i * j + j] - f[i] + mod) % mod;
        }
        pre = (pre + f[i]) % mod;
    }
    cout << (f[n] + mod) % mod << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}