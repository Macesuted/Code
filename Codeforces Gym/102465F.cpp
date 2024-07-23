/**
 * @file 102465F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 4005

typedef pair<double, int> pdi;

const double PI = acos(-1);

int x[maxn], y[maxn], w[maxn];

void solve(void) {
    int n;
    cin >> n;
    int64_t ans = INT64_MAX, sum = 0;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i] >> w[i], sum += w[i];
    for (int t = 1; t <= n; t++) {
        sum -= w[t];
        vector<pdi> S;
        for (int j = 1; j <= n; j++)
            if (t != j) S.emplace_back(atan2(y[j] - y[t], x[j] - x[t]), w[j]);

        sort(S.begin(), S.end());

        for (int i = 0; i < n - 1; i++) S.emplace_back(S[i].first + 2 * PI, S[i].second);

        int64_t tot = 0;
        for (int i = 0, j = 0; i < n - 1; i++) {
            tot -= S[i].second;
            while (S[j].first < S[i].first + PI) tot += S[j++].second;
            ans = min(ans, abs(sum - S[i].second - 2 * tot));
        }

        sum += w[t];
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