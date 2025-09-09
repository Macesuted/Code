/**
 * @file 2138A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-08
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
    int64_t k, x;
    cin >> k >> x;

    bool swp = false;
    if (x == ((int64_t)1 << k)) return cout << 0 << endl << endl, void();
    if (x > ((int64_t)1 << k)) x = ((int64_t)1 << (k + 1)) - x, swp = true;

    vector<int> ans;
    while (x != ((int64_t)1 << k))
        if (x >> k & 1)
            ans.push_back(2), x = (x - ((int64_t)1 << k)) << 1;
        else
            ans.push_back(1), x <<= 1;

    reverse(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for (auto x : ans) cout << (1 + ((x - 1) ^ swp)) << ' ';
    cout << endl;

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