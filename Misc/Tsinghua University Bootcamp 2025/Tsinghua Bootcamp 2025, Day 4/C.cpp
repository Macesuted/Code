/**
 * @file C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

bool solve(vector<string> s) {
    for (int dx = 1; dx <= 9; dx++)
        for (int dy = 1; dy <= 9; dy++)
            for (int l0 = 0, r0 = dy; r0 < (int)s[0].size(); l0++, r0++)
                for (int l1 = 0, r1 = dy; r1 < (int)s[1].size(); l1++, r1++)
                    for (int l2 = 0, r2 = dx; r2 < (int)s[2].size(); l2++, r2++)
                        for (int l3 = 0, r3 = dx; r3 < (int)s[3].size(); l3++, r3++)
                            if (s[0][l0] == s[2][l2] && s[0][r0] == s[3][l3] && s[1][l1] == s[2][r2] && s[1][r1] == s[3][r3]) {
                                vector<string> ans(18, string(18, '.'));
                                int X = max(l2, l3), Y = max(l0, l1);
                                for (int i = 0; i < (int)s[0].size(); i++) ans[X][Y - l0 + i] = s[0][i];
                                for (int i = 0; i < (int)s[1].size(); i++) ans[X + dx][Y - l1 + i] = s[1][i];
                                for (int i = 0; i < (int)s[2].size(); i++) ans[X - l2 + i][Y] = s[2][i];
                                for (int i = 0; i < (int)s[3].size(); i++) ans[X - l3 + i][Y + dy] = s[3][i];

                                cout << "Yes" << endl;
                                for (auto& s : ans) cout << s << endl;
                                return true;
                            }

    return false;
}

void solve(void) {
    vector<string> s(4);
    vector<int> id(4);
    for (int i = 0; i < 4; i++) cin >> s[i], id[i] = i;

    do {
        vector<string> t(4);
        for (int i = 0; i < 4; i++) t[id[i]] = s[i];
        if (solve(t)) return;
    } while (next_permutation(id.begin(), id.end()));

    return cout << "No" << endl, void();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}