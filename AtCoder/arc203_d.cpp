/**
 * @file arc203_d.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-03
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

#define maxn 200005

int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    set<int> S[2];
    for (int i = 1; i <= n; i++) cin >> a[i], S[a[i]].insert(i);

    int xcnt = 0;
    auto calc = [&](int p) -> bool { return p < 1 || p + 2 > n ? 0 : a[p] && !a[p + 1] && !a[p + 2]; };
    for (int i = 1; i <= n; i++) xcnt += calc(i);

    auto query = [&](void) -> int {
        if (S[0].empty()) return n;
        if (S[1].empty()) return 2;

        int x0 = xcnt, pl = *S[1].begin() - 1, pr = n - *S[1].rbegin();
        if (pr >= 2) x0--;
        if (a[1] && a[n] && !x0) return 2;
        int ans = x0 * 3 + 1;
        return min(2, pl) + ans + min(2, pr);
    };

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        S[a[x]].erase(x);
        xcnt -= calc(x - 2) + calc(x - 1) + calc(x);
        S[a[x] = !a[x]].insert(x);
        xcnt += calc(x - 2) + calc(x - 1) + calc(x);

        cout << query() << endl;
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