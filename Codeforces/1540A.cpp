/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007
// #define mod 998244353

#define maxn 100005

// namespace Math {

// int fac[maxn], inv[maxn];

// inline int C(int n, int m) {
//     if (n < m || n < 0 || m < 0) return 0;
//     return fac[n] * inv[m] % mod * inv[n - m] % mod;
// }

// int power(int a, int x) {
//     int ans = 1;
//     while (x) {
//         if (x & 1) ans = ans * a % mod;
//         a = a * a % mod;
//         x >>= 1;
//     }
//     return ans;
// }

// void INIT(int n) {
//     fac[0] = inv[0] = 1;
//     for (register int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
//     inv[n] = power(fac[n], mod - 2);
//     for (register int i = n - 1; i; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
//     return;
// }

// }  // namespace Math

// namespace Union {

// int fa[maxn];

// int getfa(int k) { return fa[k] == k ? k : fa[k] = getfa(fa[k]); }
// void merge(int x, int y) {
//     int fx = getfa(x), fy = getfa(y);
//     if (fx == fy) return;
//     fa[fy] = fx;
//     return;
// }

// }  // namespace Union

// vector<vector<int> > graph;
// void dfs(int p, int pre = 0) {
//     for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
//         if (*i != pre) {
//             dfs(*i, p);
//         }
//     return;
// }

int a[maxn];

void work(void) {
    int n;
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 2, a + n + 1);
    long long answer = 0;
    for (register int i = 2; i <= n; i++) answer -= ((i - 1) * (n - i + 1) - 1) * (a[i] - a[i - 1]);
    cout << answer << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}