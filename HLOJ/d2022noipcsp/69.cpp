/**
 * @file 69.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-13
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

string S, T;
queue<int> pos[26];

void solve(void) {
    cin >> S >> T;
    int n = S.size(), m = T.size();
    S = " " + S, T = " " + T;
    for (int i = 1; i <= m; i++) pos[T[i] - 'a'].push(i);
    int ans = INT_MAX;
    for (int i = 0, j = 0; i < n; i++) {
        if (i) {
            j++;
            while (j <= m && S[i] != T[j]) j++;
            if (j > m) break;
        }
        int minp = m + 1;
        for (int c = 0; c < S[i + 1] - 'a'; c++) {
            while (!pos[c].empty() && pos[c].front() <= j) pos[c].pop();
            if (!pos[c].empty()) minp = min(minp, pos[c].front());
        }
        ans = min(ans, minp - 1 - i);
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("string.in", "r", stdin), freopen("string.out", "w", stdout);
#endif
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