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

typedef pair<int, int> pii;

map<int, int> rec, cac;

pii a[maxn];

int n, m;

void work(void) {
    // INIT();
    cin >> n >> m;
    for (register int i = 1; i <= m; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + m + 1);
    rec[n] = 1;
    for (register int i = 1, last = -1; i <= m; i++) {
        if (last != a[i].first) {
            for (auto i : cac) rec[i.first] = i.second;
            cac.clear();
            last = a[i].first;
        }
        cac[a[i].second] = rec[a[i].second - 1] + rec[a[i].second + 1];
    }
    for (auto i : cac) rec[i.first] = i.second;
    int answer = 0;
    for (auto i : rec)
        if (i.second) answer++;
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(3) << endl;
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}