/**
 * @file 15452.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const string names[27] = {"UW",  "UJ",  "UWR", "MAP", "PW",  "AGH", "PG", "NLU", "PUT", "PO", "PWR", "SGGW", "UMCS", "UR",
                          "ZUT", "DTP", "GOO", "HUA", "KUL", "PL",  "PM", "PS",  "UAM", "UG", "UMK", "UO",   "WAT"};
int cnt[27] = {11, 9, 8, 7, 6, 5, 4, 3, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int a[8][10];

int _(string s) {
    for (int i = 0; i < 27; i++)
        if (names[i] == s) return i;
    assert(false);
}

bool dfs(int x, int y) {
    if (x && y && a[x - 1][y - 1] == a[x][y]) return false;
    if (x && a[x - 1][y] == a[x][y]) return false;
    if (x && y < 9 && a[x - 1][y + 1] == a[x][y]) return false;
    if (y && a[x][y - 1] == a[x][y]) return false;

    if (x == 7 && y == 9) return true;

    vector<int> ids;
    for (int i = 0; i < 27; i++)
        if (cnt[i]) ids.push_back(i);
    sort(ids.begin(), ids.end(), [&](int x, int y) { return cnt[x] > cnt[y]; });

    int nx = x, ny = y + 1;
    if (ny == 10) nx++, ny = 0;

    for (auto id : ids) {
        cnt[id]--;
        a[nx][ny] = id;
        if (dfs(nx, ny)) return true;
        cnt[id]++;
    }

    return false;
}

void solve(void) {
    string name;
    cin >> name;

    cnt[a[0][0] = _(name)]--;
    assert(dfs(0, 0));

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 10; j++)
            for (int dx = -1; dx <= +1; dx++)
                for (int dy = -1; dy <= +1; dy++)
                    if (dx != 0 || dy != 0) {
                        if (i + dx < 0 || i + dx > 7 || j + dy < 0 || j + dy > 9) continue;
                        if (a[i][j] == a[i + dx][j + dy]) cerr << i << ' ' << j << ' ' << dx << ' ' << dy << endl;
                    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) cout << names[a[i][j]] << ' ';
        cout << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
