/**
 * @file arc181_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-04
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

bool solve(void) {
    string a, X, Y;
    cin >> a >> X >> Y;
    int64_t n = a.size(), cnt[2][2] = {{0, 0}, {0, 0}};
    for (char c : X) cnt[0][c - '0']++;
    for (char c : Y) cnt[1][c - '0']++;
    if ((cnt[0][0] > cnt[1][0] && cnt[0][1] > cnt[1][1]) || (cnt[0][0] < cnt[1][0] && cnt[0][1] < cnt[1][1])) return false;
    int64_t x = abs(cnt[0][0] - cnt[1][0]), y = abs(cnt[0][1] - cnt[1][1]);
    if (x == 0) return true;
    if (y == 0) return false;
    if (x * n % y) return false;
    int64_t m = x * n / y;
    int len = gcd(n, m);
    for (int i = 0; i + len < n; i++)
        if (a[i] != a[i + len]) return false;
    return true;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "Yes" : "No") << endl;

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}