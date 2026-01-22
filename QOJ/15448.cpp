/**
 * @file 15448.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int pw10[5] = {1, 10, 100, 1000, 10000};

int dist[100000], cnt[25];

void solve(void) {
    int n;
    cin >> n;

    for (int i = 0; i < 100000; i++) cnt[dist[i] = 25]++;

    auto upd = [&](int p, int d) -> void {
        cnt[dist[p]]--;
        cnt[dist[p] = d]++;
        return;
    };

    int ans = 25;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        int x = stoi(s);
        if (dist[x] == 0) continue;

        queue<int> que;
        upd(x, 0), que.push(x);
        while (!que.empty()) {
            int p = que.front();
            que.pop();

            for (int t = 0; t < 5; t++)
                for (int delt : {-1, 1}) {
                    int pb = p / pw10[t] % 10, qb = (pb + 10 + delt) % 10;
                    int q = p + (qb - pb) * pw10[t];
                    if (dist[q] > dist[p] + 1) upd(q, dist[p] + 1), que.push(q);
                }
        }

        while (!cnt[ans]) ans--;

        cout << ans << ' ' << cnt[ans] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
