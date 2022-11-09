/**
 * @file 109.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-26
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

#define maxn 125

using int128_t = __int128_t;

int n, m, k, hig[5];
int128_t ans = 0, a[maxn];

void dfs(int p, int used = 0, int128_t sum = 0) {
    if (!~p) return ans = max(ans, sum), void();
    if (sum + n * (((int128_t)1 << (p + 1)) - 1) <= ans) return;
    int maxv = 0;
    for (int S = 0; S < (1 << used); S++) {
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            bool b = a[i] >> p & 1;
            for (int t = 0; t < used; t++) b ^= (!(a[i] >> hig[t] & 1) && (S >> t & 1));
            cnt += b;
        }
        maxv = max(maxv, cnt);
    }
    if (used < k && maxv != n) hig[used] = p, dfs(p - 1, used + 1, sum + ((int128_t)n << p));
    dfs(p - 1, used, sum + ((int128_t)maxv << p));
    return;
}

void solve(void) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (auto c : s) a[i] = (a[i] << 3) + (a[i] << 1) + (c ^ 48);
    }
    dfs(m - 1);
    stack<char> S;
    while (ans) S.push((ans % 10) + '0'), ans /= 10;
    while (!S.empty()) cout << S.top(), S.pop();
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("puzzle.in", "r", stdin), freopen("puzzle.out", "w", stdout);
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