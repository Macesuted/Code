/**
 * @file 81603E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

struct FastMod {
    typedef __uint128_t lll;
    typedef unsigned long long ull;
    ull m, b;
    void intt(ull M) {
        m = M;
        b = (ull)((lll(1) << 64) / M);
    }
    ull operator()(ull a) {
        ull q = (ull)((lll(b) * a) >> 64), r = a - q * m;
        return r >= m ? r - m : r;
    }
} FST[1000005];

int bsum[1000005];
unordered_set<int64_t> S;
int64_t n;

int getSum(int64_t v) { return bsum[v / 1000000] + bsum[FST[1000000](v)]; }
void check(int64_t m) {
    if (n % m == getSum(m)) S.insert(m);
    return;
}

void solve(void) {
    cin >> n;
    int64_t nl = max((int64_t)1, n - 108);
    int cnt = 0;
    for (int64_t m = 1; m * m <= n; m++) {
        int64_t nr = n - (m == 1 ? 0 : FST[m](n));
        if (nr < nl) continue;
        check(m);
        for (int64_t nc = nr; nc >= nl; nc -= m) check(nc / m), cnt++;
    }
    cout << S.size() << endl;
    S.clear();
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for (int i = 1; i <= 1000000; i++) bsum[i] = i % 10 + bsum[i / 10], FST[i].intt(i);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}