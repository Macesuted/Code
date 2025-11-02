/**
 * @file 9328.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

bool solve(void) {
    int n;
    string s;
    cin >> n >> s;

    vector<vector<int>> cnt(2, vector<int>(26, 0));
    for (int i = 0; i < n; i++) cnt[i & 1][s[i] - 'a']++;

    if (n & 1) {
        int cc[2] = {0, 0};
        for (int t = 0; t < 2; t++)
            for (int i = 0; i < 26; i++) cc[t] += cnt[t][i] & 1;
        int x = n >> 1 & 1;
        return cc[!x] == 0 && cc[x] == 1;
    }

    for (int i = 0; i < 26; i++)
        if (cnt[0][i] != cnt[1][i]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "YES" : "NO") << endl;

    return 0;
}
