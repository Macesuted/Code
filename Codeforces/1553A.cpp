/**
 * @author Macesuted (i@macesuted.moe)
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

int a[maxn];

void work(void) {
    int n, m;
    cin >> n;
    int ans = 0;
    cout << (n + 1) / 10 << endl;
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
