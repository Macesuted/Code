/**
 * @file 14136.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-11
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

void solve(void) {
    vector<string> rec;
    string line;
    while (getline(cin, line)) {
        size_t p = line.size();
        for (size_t i = 0; i < line.size(); i++)
            if (line[i] == ' ') p = i;

        if (p == line.size()) {
            rec.push_back("#");
            continue;
        }

        string s = line.substr(p + 1);

        if (line == s + ", " + s + " " + s + "ity " + s)
            rec.push_back(s + "!");
        else if (line == "i said " + s + ", " + s + " " + s + "ity " + s)
            rec.push_back(s + "@");
        else
            rec.push_back("#");
    }

    int ans = -1;

    for (size_t l = 0, r; l < rec.size(); l = r + 1) {
        r = l;
        if (rec[l].back() != '!') continue;

        size_t len = rec[l].size() - 1;
        string s = rec[l].substr(0, len);
        while (r + 1 < rec.size() && rec[r + 1].size() == len + 1 && rec[r + 1].substr(0, len) == s &&
               rec[r + 1].back() != rec[r].back())
            r++;

        ans = max(ans, int((r - l + 1) / 2 * (23 + 8 * len)));
    }

    cout << ans << endl;

    return;
}

bool mem2;

int main() {
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