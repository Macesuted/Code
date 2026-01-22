/**
 * @file 15488.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-12-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005
#define mod 1'000'000'007

int Mod(int x) { return x >= mod ? x - mod : x; }

bool f[maxn];
int n[maxn], g[maxn];

void solve(void) {
    int k, m;
    cin >> k >> m;
    for (int i = 1; i <= k; i++) cin >> n[i];
    string s;
    cin >> s;
    for (int i = 0; i <= m; i++) f[i] = (s[i] == '1');
    for (int i = 0; i < m; i++) g[i] = f[i] ^ f[i + 1];
    for (int i = 1; i < m; i++) g[i] += g[i - 1];

    int ans = 0;
    for (int i = 1; i <= k; i++) ans = Mod(ans + g[n[i] - 1]);
    bool sum = false;
    for (int i = 1; i <= k; i++) sum ^= f[n[i]];
    ans += sum;

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
