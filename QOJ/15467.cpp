/**
 * @file 15467.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005

using pli = pair<int64_t, int>;

int64_t a[maxn], v[maxn];

void solve(void) {
    int n;
    int64_t X;
    cin >> n >> X;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> v[i];

    int64_t l = 0, r = 2e18;
    while (l + 1 < r) {
        int64_t mid = (l + r) >> 1;
        ([&](int64_t lim) -> bool {
            __int128_t cnt = 0;
            for (int i = 1; i <= n; i++)
                if (lim > a[i]) cnt += (lim - a[i]) / v[i] + ((lim - a[i]) % v[i] > 0);
            return cnt <= X;
        }(mid)
                                 ? l
                                 : r) = mid;
    }

    for (int i = 1; i <= n; i++)
        if (l > a[i]) {
            int64_t c = (l - a[i]) / v[i] + ((l - a[i]) % v[i] > 0);
            a[i] += c * v[i], X -= c;
        }

    priority_queue<pli, vector<pli>, greater<pli>> que;
    for (int i = 1; i <= n; i++) que.emplace(a[i], i);
    while (X--) {
        int p = que.top().second;
        que.pop();
        que.emplace(a[p] += v[p], p);
    }

    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
