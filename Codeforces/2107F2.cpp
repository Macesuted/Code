/**
 * @file 2107F2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-05
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

#define maxn 1000005

using pll = pair<int64_t, int64_t>;

int64_t a[maxn];

pll operator-(const pll& p1, const pll& p2) { return {p1.first - p2.first, p1.second - p2.second}; }
int64_t operator*(const pll& p1, const pll& p2) { return p1.first * p2.second - p1.second * p2.first; }
bool operator<(const pll& p1, const pll& p2) { return p1 * p2 > 0; }
bool operator>(const pll& p1, const pll& p2) { return p1 * p2 < 0; }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> S;
    S.push_back(0);
    int64_t cur = 0;
    vector<pll> cvx;

    auto insert = [&](const pll& v) {
        while (!cvx.empty() && cvx.back().first >= v.first) cvx.pop_back();
        while (cvx.size() >= 2 && cvx.back() - cvx[cvx.size() - 2] > v - cvx.back()) cvx.pop_back();
        cvx.push_back(v);
        return;
    };

    for (int i = 1; i <= n; i++) {
        while (S.size() > 1 && a[S.back()] > a[i]) {
            int x = S.back();
            S.pop_back();
            cur -= (x - S.back()) * (a[x] + 1) - 1;
        }

        cur += (i - S.back()) * (a[i] + 1) - 1;
        S.push_back(i);
        insert({a[i] + 2, cur - i * (a[i] + 2)});

        int l = 0, r = cvx.size();
        while (l + 1 < r) {
            int m = (l + r) >> 1;
            (pll{1, -i} > cvx[m] - cvx[m - 1] ? l : r) = m;
        }

        int64_t ans = cvx[l].first * i + cvx[l].second;
        if (l + 1 < (int)cvx.size()) ans = min(ans, cvx[l + 1].first * i + cvx[l + 1].second);

        cout << ans << ' ';
    }

    cout << endl;

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