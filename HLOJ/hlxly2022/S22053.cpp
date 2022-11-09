/**
 * @file S22053.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-03
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

int a[14], b[14], sum[1 << 14];
int64_t f[1 << 13];

vector<int> vS;

void dfs(int p, int cnt, int S) {
    if (!p) {
        if (cnt) return;
        return vS.push_back(S);
    }

    dfs(p - 1, cnt, S);
    if (cnt) dfs(p - 1, cnt - 1, S | (1 << p));
    return;
}

void solve(void) {
    string sa;
    cin >> sa;
    int n = sa.size(), tot = 0;
    for (int i = 0; i < n; i++) tot += (a[n - i - 1] = ('0' <= sa[i] && sa[i] <= '9' ? sa[i] - '0' : sa[i] - 'a' + 10));
    if (tot % 15 != 0 || tot == 15 * n) return cout << "NO" << endl, void();
    dfs(n - 1, tot / 15, 0);
    int64_t ans = INT64_MAX;
    for (auto S : vS) {
        for (int i = 0; i < n; i++) b[i] = a[i];
        for (int i = 1; i < n; i++)
            if (S >> i & 1) b[i]++, b[i - 1] -= 16;
        if (b[n - 1] < 0 || b[n - 1] > 15) continue;
        bool chk = true;
        for (int i = 0; i < n; i++)
            if (abs(b[i]) > 15) chk = false;
        if (!chk) continue;
        sum[0] = b[n - 1];
        for (int i = 0; i < n - 1; i++) sum[1 << i] = b[i] + b[n - 1];
        for (int i = 1; i < (1 << (n - 1)); i++)
            if (i ^ (i & -i)) sum[i] = sum[i & -i] + sum[i ^ (i & -i)] - b[n - 1];
        memset(f, 0x3f, sizeof(f)), f[0] = 0;
        for (int i = 0; i < (1 << (n - 1)); i++)
            if (0 <= sum[i] && sum[i] < 16)
                for (int k = 0; k < n - 1; k++)
                    if (!(i >> k & 1)) f[i | (1 << k)] = min(f[i | (1 << k)], f[i] + ((int64_t)sum[i] << (4 * k)));
        ans = min(ans, f[(1 << (n - 1)) - 1]);
    }
    if (ans == 0x3f3f3f3f3f3f3f3f) return cout << "NO" << endl, void();
    for (int i = n - 1; ~i; i--) {
        int v = ans >> (4 * i) & 15;
        cout << char(v < 10 ? '0' + v : 'a' + v - 10);
    }
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
#endif
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