/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 1000005

// // #define mod 998244353
// #define mod 1000000007

// bool notPrime[maxn];
// vector<int> prime;
// int fac[maxn], ifac[maxn];

// int Pow(int a, int x) {
//     int ans = 1;
//     while (x) {
//         if (x & 1) ans = ans * a % mod;
//         a = a * a % mod;
//         x >>= 1;
//     }
//     return ans;
// }
// void INIT(void) {
//     fac[0] = ifac[0] = 1;
//     for (register int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
//     ifac[maxn - 1] = Pow(fac[maxn - 1], mod - 2);
//     for (register int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

//     notPrime[1] = true;
//     for (register int i = 2; i < maxn; i++) {
//         if (!notPrime[i]) prime.push_back(i);
//         for (vector<int>::iterator j = prime.begin(); i * *j < maxn; j++) {
//             notPrime[i * *j] = true;
//             if (i % *j == 0) break;
//         }
//     }
//     return;
// }

string s, t;

void work(void) {
    cin >> s >> t;
    int n = s.size(), m = t.size();
    s = ' ' + s, t = ' ' + t;
    for (register int i = 1; i <= n; i++)
        if (s[i] == t[1])
            for (register int j = i; j <= n; j++) {
                bool check = true;
                int ps = i, pt = 1;
                while (check && ps < j) {
                    ps++, pt++;
                    if (s[ps] != t[pt]) check = false;
                }
                if (!check) continue;
                while (check && pt < m) {
                    ps--, pt++;
                    if (ps < 1) check = false;
                    if (s[ps] != t[pt]) check = false;
                }
                if (check) {
                    puts("YES");
                    return;
                }
            }
    puts("NO");
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(8);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}
