/**
 * @file 10332.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int64_t s, t;
    cin >> s >> t;

    int64_t v = sqrt(s + t);
    if (v * v == s + t) return cout << "1 " << t << endl, void();

    if (s == t) {
        v = sqrt(s) + 1;
        return cout << "2 " << v * v - s << ' ' << t << endl, void();
    }

    {
        int64_t delt = abs(s - t), base = 1;
        if (delt % 2 == 1) {
            int64_t i = delt / 2;
            if (s > t && (i + 1) * (i + 1) * base > s)
                return cout << "2 " << (i + 1) * (i + 1) * base - s << ' ' << t << endl, void();
            if (s < t && i * i * base > s) return cout << "2 " << i * i * base - s << ' ' << t << endl, void();
        } else if (delt % 4 == 0) {
            int64_t q = delt / 4;
            if (!(q < 1 || (q - 1) * (q - 1) < min(s, t) || (q + 1) * (q + 1) < max(s, t)))
                return cout << "2 " << (q - 1) * (q - 1) - min(s, t) << ' ' << t << endl, void();
        }
    }

    int64_t sum = s + t;
    int64_t x = sqrt(sum + 2 * sqrt(sum) + 1) + 1;
    while (!((x * x - sum) & 1)) x++;
    int64_t y = (x * x - sum) / 2;
    cout << "3 " << x * x - s << ' ' << y * y - t << ' ' << t << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
