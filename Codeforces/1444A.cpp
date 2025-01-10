/**
 * @file 1444A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-01-05
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

typedef pair<int, int> pii;

vector<pii> split(int64_t n) {
    vector<pii> ans;
    for (int64_t v = 2; v * v <= n; v++) {
        if (n % v) continue;
        int cnt = 0;
        while (!(n % v)) n /= v, cnt++;
        ans.emplace_back(v, cnt);
    }
    if (n > 1) ans.emplace_back(n, 1);
    return ans;
}

void solve(void) {
    int64_t p, q;
    cin >> p >> q;

    vector<pii> rec = split(q);

    int64_t ans = 1;
    for (auto [v, cnt] : rec) {
        int64_t t = p;

        int gcnt = 0;
        while (t % v == 0) gcnt++, t /= v;
        if (gcnt < cnt) {
            ans = p;
            continue;
        }

        for (int i = 1; i < cnt; i++) t *= v;
        ans = max(ans, t);
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