/**
 * @file 100201C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-09
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

string _(int v, int l) {
    string s(l, '0');
    for (int i = l - 1; ~i; i--) s[i] = '0' + (v & 1), v >>= 1;
    return s;
}

void solve(void) {
    int n, m;
    cin >> n, m = n >> 1, n -= m;
    for (int r = 0; r < (1 << m); r++)
        for (int l = 0, v = r; l < (1 << n); l++, v ^= ((1 << m) - 1)) cout << _(l, n) << _(v, m) << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("code.in", "r", stdin), freopen("code.out", "w", stdout);
#endif
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