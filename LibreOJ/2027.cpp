/**
 * @file 2027.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 17
#define mod 1000000007

typedef pair<int, int> pii;

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

vector<pii> edges[maxn];
int64_t a[maxn][maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 0, x; i < n - 1; i++) {
        cin >> x;
        for (int j = 0, u, v; j < x; j++) cin >> u >> v, edges[i].emplace_back(u - 1, v - 1);
    }
    int64_t tot = 0;
    for (int S = 0; S < (1 << (n - 1)); S++) {
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n - 1; i++) {
            if (S >> i & 1) continue;
            for (auto j : edges[i])
                a[j.first][j.second]--, a[j.second][j.first]--, a[j.first][j.first]++, a[j.second][j.second]++;
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) a[i][j] = (a[i][j] + mod) % mod;
        int64_t ans = 1;
        for (int i = 1; i < n; i++) {
            int p = i;
            while (p < n && !a[p][i]) p++;
            if (p == n) {
                ans = 0;
                break;
            }
            if (p != i) ans = mod - ans;
            for (int j = i; j < n; j++) swap(a[i][j], a[p][j]);
            ans = ans * a[i][i] % mod;
            int64_t inv = Inv(a[i][i]);
            for (int j = i; j < n; j++) a[i][j] = a[i][j] * inv % mod;
            for (int j = 1; j < n; j++)
                if (i != j && a[j][i])
                    for (int k = n - 1; k >= i; k--) a[j][k] = (a[j][k] + mod - a[i][k] * a[j][i] % mod) % mod;
        }
        tot = (tot + ((__builtin_popcount(S) & 1) ? mod - 1 : 1) * ans) % mod;
    }
    cout << tot << endl;
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