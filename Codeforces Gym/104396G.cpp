/**
 * @file 104396G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-24
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

using pii = pair<int, int>;

void solve(void) {
    int n;
    int64_t C;
    cin >> n >> C;

    vector<pii> dl, dr;
    for (int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if (x < y) dr.emplace_back(x, +1), dr.emplace_back(y, -1);
        if (x > y) dl.emplace_back(y, +1), dl.emplace_back(x, -1);
    }

    sort(dl.begin(), dl.end()), sort(dr.begin(), dr.end());

    vector<pii> rec;
    rec.emplace_back(-1e9 - 1, 0);
    int lv = 0, rv = 0;
    for (auto lp = dl.begin(), rp = dr.begin(); lp != dl.end() || rp != dr.end();) {
        int x = min(lp == dl.end() ? INT_MAX : lp->first, rp == dr.end() ? INT_MAX : rp->first);
        while (lp != dl.end() && lp->first == x) lv += (lp++)->second;
        while (rp != dr.end() && rp->first == x) rv += (rp++)->second;
        int v = max({int(lp != dl.end() || rp != dr.end()), lv, rv});
        if (v != rec.back().second) rec.emplace_back(x, v);
    }

    stack<int> S;
    S.push(0);
    int64_t ans = 0;
    for (int i = 1; i + 1 < (int)rec.size(); i++) {
        int len = rec[i + 1].first - rec[i].first;
        ans += (int64_t)len * 2 * rec[i].second + abs(rec[S.top()].second - rec[i].second) * C;
        while (S.size() > 1 && rec[S.top()].second < rec[i].second && rec[i].first - rec[S.top()].first < C) {
            auto t = S.top();
            S.pop();
            int delt = min(rec[S.top()].second, rec[i].second) - rec[t].second;
            ans -= delt * 2 * (C - (rec[i].first - rec[t].first)), rec[t].second += delt;
            if (rec[S.top()].second > rec[t].second) S.push(t);
        }
        if (rec[S.top()].second < rec[i].second)
            while (!S.empty()) S.pop();
        if (S.empty() || rec[S.top()].second > rec[i].second) S.push(i);
    }
    cout << ans + rec[S.top()].second * C << endl;

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