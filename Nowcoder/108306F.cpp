/**
 * @file 108306F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using pii = pair<int, int>;

pii s1, s2, t1, t2;

void solve(void) {
    cin >> s1.first >> s1.second;
    cin >> s2.first >> s2.second;
    cin >> t1.first >> t1.second;
    cin >> t2.first >> t2.second;
    if (((s1.first + s1.second) & 1) != ((t1.first + t1.second) & 1)) swap(t1, t2);

    auto dist = [&](pii x, pii y) -> int64_t { return max(abs(x.first - y.first), abs(x.second - y.second)); };

    cout << dist(s1, t1) + dist(s2, t2) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}