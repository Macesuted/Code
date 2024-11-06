/**
 * @file 9565.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-06
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

void solve(void) {
    string s;
    cin >> s;
    for (int i = 1; i < (int)s.size(); i += 2)
        if (s[i] == '0')
            s[i] = '1';
        else if (s[i] == '1')
            s[i] = '0';

    int cnt[3] = {0, 0, 0};
    for (auto i : s) cnt[i - '0']++;

    int ans = abs(cnt[0] - cnt[1]) - cnt[2];
    if (ans < 0) ans = abs(ans % 2);

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