/**
 * @file 10431.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int64_t p, q;
    cin >> p >> q;

    stringstream ans;
    if ((p + q) & 1) ans << "12+", p -= 12, q -= 21;

    int64_t X = (p + q) >> 1, Y = (p - q) >> 1;
    bool revX = false, revY = false;
    if (X < 0) X = -X, revX = true;
    if (Y < 0) Y = -Y, revY = true;

    auto gen = [&](int b, int v) -> int64_t {
        int64_t ans = 0;
        while (b--) ans = ans * 10 + v;
        return ans;
    };
    vector<int64_t> nums;
    for (int b = 1; b < 18; b++)
        for (int v = 1; v < 10; v++) nums.push_back(gen(b, v));

    ans << '0';
    while (X) {
        int64_t v = *(--upper_bound(nums.begin(), nums.end(), X));
        ans << "+-"[revX] << v, X -= v;
    }
    ans << "+-"[revX] << '0';

    while (Y) {
        int64_t v = *(--upper_bound(nums.begin(), nums.end(), Y));
        ans << '+' << (revY ? 0 : v) << '-' << (revY ? v : 0), Y -= v;
    }

    cout << ans.str() << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}