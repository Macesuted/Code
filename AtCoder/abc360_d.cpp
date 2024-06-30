/**
 * @file abc360_d.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
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

vector<int64_t> pos[2];

void solve(void) {
    int n, t;
    cin >> n >> t, t *= 2;
    string s;
    cin >> s;
    for (int i = 1, x; i <= n; i++) cin >> x, pos[s[i - 1] - '0'].push_back(x);
    sort(pos[0].begin(), pos[0].end()), sort(pos[1].begin(), pos[1].end());
    int64_t ans = 0;
    for (auto x : pos[1]) {
        int p1 = lower_bound(pos[0].begin(), pos[0].end(), x) - pos[0].begin(),
            p2 = upper_bound(pos[0].begin(), pos[0].end(), x + t) - pos[0].begin();
        ans += p2 - p1;
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
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}