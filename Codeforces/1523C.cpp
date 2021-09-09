/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 * @brief My Solution: https://www.macesuted.cn/article/cf1523c/
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007
// #define mod 998244353
#define maxn 1005

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

int a[maxn];

int n;

list<int> li;

void work(void) {
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    for (register int i = 1; i <= n; i++) {
        if (a[i] == 1)
            li.push_back(1);
        else {
            while (!li.empty() && li.back() != a[i] - 1) li.pop_back();
            if (!li.empty()) li.pop_back();
            li.push_back(a[i]);
        }
        for (list<int>::iterator j = li.begin(); j != li.end(); j++) {
            if (j != li.begin()) cout << '.';
            cout << *j;
        }
        cout << endl;
    }
    li.clear();
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