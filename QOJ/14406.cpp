/**
 * @file 14406.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int p[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) cin >> p[i];

    set<int> S;

    auto rev = [&](int p) {
        if (!p) return;
        if (S.count(p))
            S.erase(p);
        else
            S.insert(p);
        return;
    };

    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (x) rev(i), rev(p[i]);
    }

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        rev(x), rev(p[x]);
        cout << S.size() << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
