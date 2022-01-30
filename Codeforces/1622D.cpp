/**
 * @file 1622D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 5005
#define mod 998244353

bool a[maxn];
int sum[maxn], binom[maxn][maxn];
vector<int> pos;

void solve(void) {
    int n, k;
    cin >> n >> k;
    pos.push_back(0);
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        a[i] = (c == '1');
        sum[i] = sum[i - 1] + a[i];
        if (a[i]) pos.push_back(i);
    }
    pos.push_back(n + 1);
    if (sum[n] < k || k == 0) return cout << 1 << endl, void();
    long long ans = 0;
    for (int l = 0, r = k + 1; r < (int)pos.size(); l++, r++) {
        int pl = pos[l] + 1, pr = pos[r] - 1, p2 = pos[l + 1];
        ans = (ans + mod + binom[pr - pl + 1][k] - binom[pr - p2][k - 1]) % mod;
        if (r + 1 == (int)pos.size()) ans = (ans + binom[pr - p2][k - 1]) % mod;
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 0; i < maxn; i++) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; j++) binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
    }

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
