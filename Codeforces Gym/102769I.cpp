/**
 * @file 102769I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-09
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

int64_t gcd(int64_t x, int64_t y) { return y ? gcd(y, x % y) : x; }
int64_t exgcd(int64_t x, int64_t y, int64_t& a, int64_t& b) {
    if (y == 0) return a = 1, b = 0, x;
    int64_t g = exgcd(y, x % y, b, a);
    return b -= x / y * a, g;
}

int64_t solve(void) {
    int q;
    cin >> q;
    int64_t a = 0, b = 0, c = 0, ans = 0;
    while (q--) {
        int64_t t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            int64_t px, py, g = exgcd(b, y, px, py);
            c = gcd(c, abs(x * b - y * a) / g), tie(a, b) = make_pair(px * a + py * x, g);
            if (c) a = (a % c + c) % c;
        } else {
            int w;
            cin >> w;
            if ((b == 0 && y != 0) || (b != 0 && y % b != 0)) continue;
            if (b != 0) x = abs(x - y / b * a);
            if ((c == 0 && x != 0) || (c != 0 && x % c != 0)) continue;
            ans += w;
        }
    }
    return ans;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int64_t _ = 1;
    cin >> _;
    for (int i = 1; i <= _; i++) cout << "Case #" << i << ": " << solve() << endl;

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}