/**
 * @file 1748B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-12
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

int cnt[10];

void solve(void) {
    int n, ans = 0;
    string s;
    cin >> n >> s, s = " " + s;
    for (int l = 1, x; l <= n; l++) {
        x = 0, memset(cnt, 0, sizeof(cnt));
        for (int r = l; r <= min(n, l + 99); r++) {
            int c = s[r] - '0';
            if (!(cnt[c]++)) x++;
            bool chk = true;
            for (int i = 0; i < 10; i++) chk &= (cnt[i] <= x);
            ans += chk;
        }
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