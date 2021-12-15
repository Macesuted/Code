#include <bits/stdc++.h>
using namespace std;

#define mod 998244353
#define maxn 1000005

long long fac[maxn];

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}

void solve(void) {
    int n, k;
    cin >> n >> k;
    long long ans = fac[k - 1];
    if (n - k > 0) ans = ans * k % mod;
    if (n - k > 1) ans = ans * Pow(n, n - k - 1) % mod;
    cout << ans << endl;
    return;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ios::sync_with_stdio(false);
    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}