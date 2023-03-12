/**
 * @file C23028.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define mod1 1000000007
#define mod2 1000000009

typedef pair<int, int> pii;

map<pii, int64_t> cnt;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        int64_t v1 = 0, v2 = 0;
        for (auto i : s) v1 = (v1 * 1331 + i) % mod1, v2 = (v2 * 1331 + i) % mod2;
        cnt[{v1, v2}]++;
    }
    int64_t ans = 0;
    for (auto i : cnt) ans += i.second * i.second * i.second;
    cout << ans % mod1 << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("recall.in", "r", stdin), freopen("recall.out", "w", stdout);
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