/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007
// #define mod 998244353
#define maxn 805

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

int a[maxn][maxn], b[maxn][maxn];
vector<int> numbers;

int n, k;

bool check(int lim) {
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++)
            b[i][j] = (a[i][j] <= lim);
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++)
            b[i][j] = b[i][j] + b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
    for (register int i = k; i <= n; i++)
        for (register int j = k; j <= n; j++)
            if (b[i][j] - b[i - k][j] - b[i][j - k] + b[i - k][j - k] >= ((k * k + 1) / 2))
                return true;
    return false;
}

void work(void) {
    // INIT();
    cin >> n >> k;
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++)
            cin >> a[i][j], numbers.push_back(a[i][j]);
    sort(numbers.begin(), numbers.end());
    int l = 0, r = n * n - 1;
    if (check(numbers[l])) return cout << numbers[l] << endl, void();
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        check(numbers[mid]) ? r = mid : l = mid;
    }
    cout << numbers[r] << endl;
    numbers.clear();
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