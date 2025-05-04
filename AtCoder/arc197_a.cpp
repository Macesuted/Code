/**
 * @file arc197_a.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    int n, m;
    string s;
    cin >> n >> m >> s, s = ' ' + s;

    int cnt[2] = {n - 1, m - 1};

    for (int i = 1; i <= n + m - 2; i++) {
        if (s[i] == 'D') cnt[0]--;
        if (s[i] == 'R') cnt[1]--;
    }

    int64_t ans = 1;
    for (int i = 1, cur = 0; i <= n + m - 2; i++) {
        if (s[i] == '?') cur++;
        ans += min(cur, cnt[0]) - max(0, cur - cnt[1]) + 1;
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}