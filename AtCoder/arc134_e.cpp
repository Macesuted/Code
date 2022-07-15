/**
 * @file arc134_e.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 205
#define mod 998244353

int a[maxn], f[maxn][1 << 16];
bool lose[1 << 16];

bool check(const set<int>& s) {
    if (s.size() == 1 && (*s.begin() == 1 || *s.begin() == 2)) return false;
    if (s.size() == 2 && *s.begin() == 4 && *s.rbegin() == 8) return false;
    for (auto i : s)
        if (i % 12) return true;
    int S = 0;
    for (auto i : s) S |= 1 << (i / 12 - 1);
    return !lose[S];
}

void solve(void) {
    int n;
    cin >> n;
    int64_t ans = 1;
    for (int i = 1; i <= n; i++) cin >> a[i], ans = ans * a[i] % mod;
    ans = (ans + mod - 2) % mod;
    for (int i = 1; i <= n; i++)
        if (a[i] == 1) {
            ans = (ans + 1) % mod;
            break;
        }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int S = 0; S < 4; S++)
            if (f[i - 1][S])
                for (int j = 0; j < 2 && 4 * (j + 1) <= a[i]; j++)
                    f[i][S | (1 << j)] = (f[i][S | (1 << j)] + f[i - 1][S]) % mod;
    ans = (ans + mod - f[n][3]) % mod;
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int S = 0; S < (1 << 16); S++)
            if (f[i - 1][S])
                for (int j = 0; j < 16 && 12 * (j + 1) <= a[i]; j++)
                    f[i][S | (1 << j)] = (f[i][S | (1 << j)] + f[i - 1][S]) % mod;
    for (int S = 0; S < (1 << 16); S++)
        if (lose[S]) ans = (ans + mod - f[n][S]) % mod;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int S = 1; S < (1 << 16); S++) {
        int maxVal = 0;
        for (int i = 0; i < 16; i++)
            if (S >> i & 1) maxVal = max(maxVal, (i + 1) * 12);
        lose[S] = true;
        for (int i = 1; i <= maxVal; i++) {
            set<int> s;
            for (int j = 0; j < 16; j++)
                if (S >> j & 1) s.insert((j + 1) * 12 % i);
            s.erase(0);
            if (!check(s)) {
                lose[S] = false;
                break;
            }
        }
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}