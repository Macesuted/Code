/**
 * @file nikkei2019_qual_f.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

typedef pair<int64_t, int> pii;

vector<vector<int64_t>> rec;
vector<pii> vec;
multiset<pii> S1, S2, S3, T1, T2;
int cnt[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k, rec.resize(k + 1);
    for (int i = 1, c, v; i <= n; i++) cin >> c >> v, rec[c].push_back(v * 2);
    for (int i = 1; i <= k; i++) {
        sort(rec[i].begin(), rec[i].end(), greater<int64_t>());
        rec[i][0] = rec[i][1] = (rec[i][0] + rec[i][1]) / 2;
        for (auto j : rec[i]) vec.emplace_back(j, i);
        S2.emplace(rec[i][0] + rec[i][1], i);
        if (rec[i].size() > 2) S3.emplace(rec[i][0] + rec[i][1] + rec[i][2], i);
    }
    sort(vec.begin(), vec.end(), greater<pii>());
    int64_t tot = 0;
    for (auto [v, p] : vec) {
        int64_t ans = -2;
        if (cnt[p]++) {
            ans = tot + v;
            if (cnt[p] > 2) T1.emplace(v, p), S1.erase(S1.find({v, p}));
            if (cnt[p] == 2) T2.emplace(2 * v, p);
            if (cnt[p] == 3) T2.erase({2 * rec[p][0], p});
        } else {
            if (!S1.empty()) ans = max(ans, tot + S1.rbegin()->first);
            if (!S2.empty() && !T1.empty()) ans = max(ans, tot + S2.rbegin()->first - T1.begin()->first);
            if (!S3.empty() && !T2.empty()) ans = max(ans, tot + S3.rbegin()->first - T2.begin()->first);
            for (int j = 2; j < (int)rec[p].size(); j++) S1.emplace(rec[p][j], p);
            S2.erase({2 * v, p});
            if (rec[p].size() > 2) S3.erase({2 * v + rec[p][2], p});
        }
        tot += v, cout << ans / 2 << endl;
    }
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