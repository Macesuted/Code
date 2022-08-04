/**
 * @file 1238G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 500005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

tiii a[maxn];
map<int, int> S;

void solve(void) {
    int n, m, c, c0;
    cin >> n >> m >> c >> c0;
    for (int i = 1; i <= n; i++) cin >> get<0>(a[i]) >> get<1>(a[i]) >> get<2>(a[i]);
    sort(a + 1, a + n + 1), S.clear(), S[0] = c0;
    int64_t ans = 0, sum = c0;
    get<0>(a[n + 1]) = m;
    for (int i = 1, v, p, l; i <= n + 1; i++) {
        tie(p, l, v) = a[i];
        int t = p - get<0>(a[i - 1]), x;
        sum -= t;
        while (!S.empty() && t >= S.begin()->second)
            ans += 1LL * S.begin()->first * S.begin()->second, t -= S.begin()->second, S.erase(S.begin());
        if (!S.empty() && t)
            x = S.begin()->first, ans += 1LL * x * t, t = S.begin()->second - t, S.erase(S.begin()), S.emplace(x, t),
            t = 0;
        if (t) return cout << -1 << endl, void();
        S[v] += l, sum += l;
        while (!S.empty() && sum - S.rbegin()->second >= c) sum -= S.rbegin()->second, S.erase(--S.end());
        if (sum > c) tie(x, t) = *S.rbegin(), S.erase(--S.end()), S.emplace(x, t - (sum - c)), sum = c;
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