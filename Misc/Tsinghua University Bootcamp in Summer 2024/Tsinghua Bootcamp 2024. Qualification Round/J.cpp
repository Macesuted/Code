/**
 * @file J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1005
#define mod 998244353

int64_t pow2[maxn];
vector<int> a[maxn];
bool conf[1 << 21];
bitset<maxn> SS[1 << 21];

void solve(void) {
    int n, m;
    cin >> n >> m;

    pow2[0] = 1;
    for (int i = 1; i <= n; i++) pow2[i] = pow2[i - 1] * 2 % mod;

    for (int i = 0; i < m; i++) {
        int s;
        cin >> s;
        a[i].resize(s);
        for (int j = 0; j < s; j++) cin >> a[i][j];
    }
    for (int i = 0; i < m; i++) {
        set<int> S;
        for (auto x : a[i]) S.insert(x);
        for (int j = 0; j < m; j++) {
            for (auto x : a[j])
                if (S.count(-x)) conf[(1 << i) | (1 << j)] = true;
        }
    }

    for (int S = 1; S < (1 << m); S++) {
        int T = S & (-S);
        conf[S] |= conf[S ^ T];
        for (int i = 0; i < m; i++)
            if (S >> i & 1) conf[S] |= conf[(1 << i) | T];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n; j++) SS[1 << i][j] = 1;
        for (auto j : a[i]) SS[1 << i][abs(j)] = 0;
    }

    int64_t ans = pow2[n];
    for (int S = 1; S < (1 << m); S++) {
        int64_t x = 1, T = S & (-S);
        for (int j = 0; j < m; j++)
            if (S >> j & 1) x = mod - x;
        if (S != T) SS[S] = SS[S ^ T] & SS[T];
        if (conf[S]) continue;
        ans = (ans + x * pow2[SS[S].count()]) % mod;
    }
    cout << ans << endl;

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