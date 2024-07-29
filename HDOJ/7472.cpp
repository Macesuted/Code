/**
 * @file 7472.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int read() {
    char ch = getchar();
    int res = 0, f = +1;
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -f;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = res * 10 + ch - '0';
        ch = getchar();
    }
    return res * f;
}

int a[20], w[1 << 20], f[1 << 20], xorS[1 << 20], ans, n2, m2;
bool vis[1 << 20];
vector<pii> rec;

void check(int S, int T, int val) {
    f[S | T] = min(f[S | T], w[xorS[T]]);
    ans = min(ans, max(f[S | T], f[(n2 - 1) ^ (S | T)]) - val);
    return;
};

void solve(void) {
    int n = read(), m = read();
    n2 = 1 << n, m2 = 1 << m;
    for (int i = 0; i < n; i++) a[i] = read();
    for (int i = 0; i < m2; i++) w[i] = read();
    for (int i = 0; i < n2; i++) vis[i] = false, f[i] = INT_MAX;
    for (int S = 0; S < n2; S++) {
        xorS[S] = 0;
        for (int j = 0; j < n; j++)
            if (S >> j & 1) xorS[S] ^= a[j];
    }

    rec.clear();
    for (int S = 0; S < n2; S++) rec.emplace_back(w[xorS[S]], S);
    sort(rec.begin(), rec.end(), greater<pii>());

    ans = INT_MAX;
    for (auto [val, S] : rec) {
        vis[S] = true;
        for (int fT = S ^ (n2 - 1), T = fT; T; T = (T - 1) & fT)
            if (vis[T]) check(S, T, val);
        if (vis[0]) check(S, 0, val);
    }

    cout << ans << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = read();
    while (_--) solve();

    return 0;
}