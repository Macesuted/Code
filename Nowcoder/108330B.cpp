/**
 * @file 108330B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int64_t a, b, c;
    cin >> a >> b >> c;

    if (a == c && b == c) return cout << 0 << endl << endl, void();

    if (a == 0 && b == 0) return cout << -1 << endl, void();

    vector<int> ans;

    int apos = -1, bpos = -1;
    while (((int64_t)1 << (apos + 1)) <= a) apos++;
    while (((int64_t)1 << (bpos + 1)) <= b) bpos++;

    if (apos < bpos) ans.push_back(3), a ^= b, apos = bpos;
    if (apos > bpos) ans.push_back(4), b ^= a, bpos = apos;

    for (int i = 30; ~i; i--) {
        if ((a >> bpos & 1) ^ (c >> i & 1)) ans.push_back(3), a ^= b;
        if (i == 0) break;
        if (apos < 30)
            ans.push_back(1), a <<= 1, apos++;
        else
            ans.push_back(2), b >>= 1, bpos--;
    }
    assert(bpos == 0);
    assert(a == c);
    ans.push_back(2), b >>= 1;
    assert(b == 0);
    ans.push_back(4), b = a;
    assert(a == b && a == c);

    cout << ans.size() << endl;
    for (auto x : ans) cout << x << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
