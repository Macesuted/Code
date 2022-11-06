/**
 * @file 1750B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-06
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

void solve(void) {
    int n;
    string s;
    cin >> n >> s, s = " " + s;
    int64_t ans = 0;
    int cnt[2] = {0, 0};
    for (int i = 1; i <= n; i++) cnt[s[i] - '0']++;
    if (cnt[0] > 0 && cnt[1] > 0) ans = max(ans, (int64_t)cnt[0] * cnt[1]);
    for (int i = 2, p = 1; i <= n + 1; i++)
        if (i == n + 1 || s[i] != s[i - 1]) ans = max(ans, (int64_t)(i - p) * (i - p)), p = i;
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