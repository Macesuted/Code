/**
 * @file 11378.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-13
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

int pel[20];

void solve(void) {
    int n, a, b, m;
    cin >> n >> a >> b >> m;

    for (int i = 0; i < n; i++) pel[i] = 0;

    int ta = 0, tb = 0;
    priority_queue<int, vector<int>, greater<int>> pd;
    for (int i = 1; i <= m; i++) {
        int t;
        char p;
        string v;
        cin >> t >> p >> v;

        if (pel[p - 'A'] == -1) continue;

        if (v == "ac") {
            ta++, tb += pel[p - 'A'] * 20 + t, pel[p - 'A'] = -1;
            continue;
        }

        if (v == "rj") {
            pel[p - 'A']++;
            continue;
        }

        pd.push(pel[p - 'A'] * 20 + t), pel[p - 'A'] = -1;
    }

    int ans = 0;
    while (ta < a || (ta == a && tb >= b)) {
        if (pd.empty()) return cout << -1 << endl, void();
        ta++, tb += pd.top(), pd.pop(), ans++;
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