/**
 * @file 12962.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 305
#define mod 1000000007
#define M 60

int a[M][3005], len[M], f[2][M][maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

void solve(void) {
    int n;
    cin >> n;
    auto repeat = [](string s, int tim) {
        string t;
        while (tim--) t.append(s);
        return t;
    };
    for (int i = 1; i <= n; i++) {
        int l;
        string base, s;
        cin >> l >> s;
        s = repeat(s, M / __gcd(M, l)), l /= __gcd(M, l);
        int t = l;
        if (l % 2 == 0) s = repeat(s, 32 / l), t = 2;
        if (l % 3 == 0) s = repeat(s, 27 / l), t = 3;
        if (l % 5 == 0) s = repeat(s, 25 / l), t = 5;
        if (l % 7 == 0) s = repeat(s, 49 / l), t = 7;
        len[t] = max(len[t], (int)s.size());
        for (int i = 0; i < (int)s.size(); i++) a[t][i] += (s[i] == 'O');
    }
    for (int i = 0; i < M; i++) f[0][i][0] = 1;
    bool t = false;
    int64_t ans = Inv(M);
    for (int i = 1; i <= 50; i++) {
        ans = ans * i % mod;
        if (!len[i]) continue;
        t = !t;
        memset(f[t], 0, sizeof(f[t]));
        ans = ans * Inv(len[i] / M) % mod;
        for (int j = 0; j < len[i]; j++)
            for (int k = a[i][j]; k <= n; k++) f[t][j % M][k] = (f[t][j % M][k] + f[!t][j % M][k - a[i][j]]) % mod;
    }
    for (int i = 1; i <= n; i++) {
        int64_t sum = 0;
        for (int j = 0; j < M; j++) sum = (sum + f[t][j][i]) % mod;
        cout << ans * sum % mod << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("meeting.in", "r", stdin), freopen("meeting.out", "w", stdout);
#endif
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
