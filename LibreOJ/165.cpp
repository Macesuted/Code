/**
 * @file 165.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 3005
#define mod 998244353

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

int64_t X[maxn], Y[maxn], f[maxn];

int64_t calc(int x, int cnt) {
    for (int i = 1; i <= cnt; i++)
        if (X[i] == x) return Y[i];
    int64_t ans = 0;
    for (int i = 1; i <= cnt; i++) ans = (ans + Y[i] * Inv(f[i] * (x + mod - X[i]) % mod)) % mod;
    for (int i = 1; i <= cnt; i++) ans = ans * (x + mod - X[i]) % mod;
    return ans;
}

void solve(void) {
    int n, cnt = 0;
    cin >> n;
    while (n--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            X[++cnt] = x, Y[cnt] = y, f[cnt] = 1;
            for (int i = 1; i < cnt; i++)
                f[i] = f[i] * (X[i] + mod - X[cnt]) % mod, f[cnt] = f[cnt] * (X[cnt] + mod - X[i]) % mod;
        } else {
            int x;
            cin >> x;
            cout << calc(x, cnt) << endl;
        }
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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