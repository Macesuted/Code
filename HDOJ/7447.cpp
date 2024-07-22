/**
 * @file 7447.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef tuple<int, int, int> tiii;

int a[20][20];

vector<tiii> ans;
void chk(int x, int y, int z) {
    int t = min({x, y, z});
    if (t == y) tie(x, y, z) = make_tuple(y, z, x);
    if (t == z) tie(x, y, z) = make_tuple(z, x, y);
    if (x == 1) {
        if (y == 2 && z == 3) return;
        if (y == 3 && z == 4) return;
        if (y == 4 && z == 5) return;
        if (y == 5 && z == 2) return;
    }
    if (x == 2) {
        if (y == 5 && z == 6) return;
        if (y == 6 && z == 3) return;
    }
    if (x == 3) {
        if (y == 6 && z == 4) return;
    }
    if (x == 4) {
        if (y == 6 && z == 5) return;
    }
    ans.emplace_back(x, min(y, z), max(y, z));
    return;
}

void solve(void) {
    ans.clear();
    for (int i = 1; i <= 9; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= 12; j++)
            if (s[j - 1] == '*')
                a[i][j] = -1;
            else
                a[i][j] = s[j - 1] - '0';
    }
    chk(a[3][6], a[4][6], a[4][7]);
    chk(a[1][6], a[4][9], a[4][10]);
    chk(a[1][4], a[4][12], a[4][1]);
    chk(a[3][4], a[4][3], a[4][4]);

    chk(a[7][4], a[6][4], a[6][3]);
    chk(a[9][4], a[6][1], a[6][12]);
    chk(a[9][6], a[6][10], a[6][9]);
    chk(a[7][6], a[6][7], a[6][6]);

    if (ans.empty()) return cout << "No problem" << endl, void();
    cout << get<0>(ans.front()) << ' ' << get<1>(ans.front()) << ' ' << get<2>(ans.front()) << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}
