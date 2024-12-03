/**
 * @file 2042C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-03
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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> rec;
    for (int i = n - 1, cnt = 0; i; i--) {
        if (s[i] == '0')
            cnt--;
        else
            cnt++;
        rec.push_back(cnt);
    }
    sort(rec.begin(), rec.end());
    int ans = 1;
    while (!rec.empty() && rec.back() > 0 && k > 0) k -= rec.back(), rec.pop_back(), ans++;
    if (k > 0)
        cout << -1 << endl;
    else
        cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. <<     "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}