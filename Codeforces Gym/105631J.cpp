/**
 * @file 105631J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-03
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

vector<int64_t> vals[2][62];

int highbit(int64_t v) {
    for (int i = 60; ~i; i--)
        if (v >> i & 1) return i;
    return 61;
}
void insert(int b, int64_t v) { return vals[b][highbit(v)].push_back(v), void(); }

void solve(void) {
    int n;
    int64_t L;
    cin >> n >> L;
    for (int i = 0; i < 62; i++) vals[0][i].clear(), vals[1][i].clear();
    for (int i = 1; i <= n; i++) {
        int64_t v;
        cin >> v;
        vals[0][highbit(v)].push_back(v);
    }
    int64_t ans = 0;
    for (int t = 59; ~t; t--) {
        sort(vals[0][t].begin(), vals[0][t].end()), sort(vals[1][t].begin(), vals[1][t].end());

        if (vals[0][t].empty() && vals[1][t].empty()) continue;
        ans |= (int64_t)1 << t;
        if (!(L >> t & 1)) {
            if (vals[0][t].size() + vals[1][t].size() > 1) {
                ans |= ((int64_t)1 << t) - 1;
                break;
            }
            if (!vals[0][t].empty())
                insert(1, vals[0][t][0] ^ ((int64_t)1 << t));
            else
                insert(1, vals[1][t][0] ^ ((int64_t)1 << t));
        } else {
            for (auto v : vals[0][t]) insert(0, v ^ ((int64_t)1 << t));
            if (vals[0][t].empty()) insert(1, vals[1][t].back() ^ ((int64_t)1 << t)), vals[1][t].pop_back();
            if (!vals[1][t].empty()) {
                ans |= ((int64_t)1 << t) - 1;
                break;
            }
        }
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}