/**
 * @file 2073G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

bool solve(void) {
    int n, m;
    string s, t;
    cin >> m >> n >> t >> s;
    m = t.size(), n = s.size();
    int pl = 0, pr = 0;
    while (pl < n && s[pl] == '1') pl++;
    if (pl == n) {
        for (auto c : t)
            if (c == '0') return false;
        return true;
    }
    while (pr < n && s[n - pr - 1] == '1') pr++;

    for (int i = 0; i < pl; i++)
        if (t[i] == '0') return false;
    for (int i = 0; i < pr; i++)
        if (t[m - 1 - i] == '0') return false;

    s = s.substr(pl, n - pl - pr), t = t.substr(pl, m - pl - pr);
    if (s.empty()) return true;
    s.pop_back();
    n = s.size(), m = t.size();

    vector<int> cnt;
    int cur = 0;
    for (auto c : t)
        if (c == '0')
            cnt.push_back(cur), cur = 0;
        else
            cur++;
    if (cnt.empty()) return false;

    for (int l = 0, r, p = 0; l < n; l = r + 1) {
        r = l;
        while (r + 1 < n && s[l] == s[r + 1]) r++;
        if (s[l] == '0')
            p += r - l + 1;
        else
            while (p < (int)cnt.size() && cnt[p] < r - l + 1) p++;
        if (p >= (int)cnt.size()) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "yes" : "no") << endl;

    return 0;
}