/**
 * @file 14559.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using tiii = tuple<int, int, int>;

void printx(const string& s, const vector<tiii>& rec) {
    cout << s << ' ' << rec.size() << endl;
    for (auto [x, y, z] : rec) cout << x << ' ';
    cout << endl;
    for (auto [x, y, z] : rec) cout << y << ' ';
    cout << endl;
    for (auto [x, y, z] : rec) cout << z << ' ';
    cout << endl;
    return;
}

void makePre(string cmd, int l, int r) {
    for (int i = 1; i < 32; i++) {
        vector<tiii> rec;
        for (int x = l + i; x <= r; x += 32) rec.emplace_back(x - 1, x, x);
        printx(cmd, rec);
    }
    for (int i = l + 32; i <= r; i += 32) {
        vector<tiii> rec;
        for (int j = i; j < i + 32; j++) rec.emplace_back(i - 1, j, j);
        printx(cmd, rec);
    }
    return;
}

void solve(void) {
    cout << 188 << endl;

    makePre("add", 0, 1023);

    vector<tiii> rec;
    for (int i = 0; i < 1024; i++) {
        rec.emplace_back(i, i | (1 << 10), i | (1 << 10));
        if (rec.size() == 32) printx("mul", rec), rec.clear();
    }

    makePre("max", 1024, 2047);

    for (int i = 0; i < 1024; i++) {
        rec.emplace_back(i, i | (1 << 10), i);
        if (rec.size() == 32) printx("sub", rec), rec.clear();
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
