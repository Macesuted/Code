/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007
// #define mod 998244353
#define maxn 200005

long long fac[maxn], inv[maxn];

long long power(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

inline long long C(int n, int m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }
void INIT(void) {
    fac[0] = inv[0] = 1;
    for (register int i = 1; i < maxn; i++) fac[i] = fac[i - 1] % mod;
    inv[maxn - 1] = power(fac[maxn - 1], mod - 2);
    for (register int i = maxn - 2; i; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
    return;
}

int n, m;

void work(void) {
    cin >> n >> m;
    static string str, cac;
    cin >> str;
    str = ' ' + str + ' ';
    cac = str;
    while (m--) {
        bool move = false;
        for (register int i = 1; i <= n; i++)
            if (str[i] == '0' && (str[i - 1] == '1' || str[i + 1] == '1') && !(str[i - 1] == '1' && str[i + 1] == '1'))
                cac[i] = '1', move = true;
        str = cac;
        if (!move) break;
    }
    for (register int i = 1; i <= n; i++) cout << str[i];
    cout << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(3) << endl;
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}