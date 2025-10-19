/**
 * @file 14606.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-10-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int n, m;
    cin >> n >> m;

    vector<vector<vector<int>>> cats(m + 1);
    for (int i = 1, p, k, x; i <= n; i++) {
        cin >> p >> k;
        vector<int> rec;
        while (k--) cin >> x, rec.push_back(x);
        cats[p].push_back(rec);
    }

    vector<int> cnt(m + 1, 0);
    for (int i = 1; i <= m; i++)
        for (auto &c : cats[i])
            for (auto x : c) cnt[x]++;

    set<int> avai;
    for (int i = 1; i <= m; i++)
        if (!cnt[i]) avai.insert(i);

    for (int i = 1; i <= m; i++) {
        if (cats[i].empty()) {
            if (avai.empty()) return cout << "no" << endl, void();
            avai.erase(avai.begin());
            continue;
        }

        map<int, int> ccnt;
        for (auto &c : cats[i])
            for (auto x : c) {
                ccnt[x]++;
                if (!--cnt[x]) avai.insert(x);
            }

        bool fnd = false;
        for (auto [x, xcnt] : ccnt)
            if (xcnt == (int)cats[i].size() && avai.count(x)) {
                avai.erase(x), fnd = true;
                break;
            }

        if (!fnd) return cout << "no" << endl, void();
    }

    return cout << "yes" << endl, void();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}