/**
 * @file 8960.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

bool solve(int n, string s, int64_t k) {
    int64_t c = (int64_t)1 << (n - 1);
    if (k == c) return false;
    if (k < c)
        if (s[n - 1] == '0')
            return !solve(n - 1, s, c - k);
        else
            return solve(n - 1, s, k);
    else if (s[n - 1] == '0')
        return solve(n - 1, s, k - c);
    else
        return !solve(n - 1, s, 2 * c - k);
}

void solve(void) {
    int n;
    int64_t k;
    string s;
    cin >> n >> k >> s, reverse(s.begin(), s.end());
    cout << (solve(n, s, k) ? "Up" : "Down") << endl;
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