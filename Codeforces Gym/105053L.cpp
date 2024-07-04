/**
 * @file 105053L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-03
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

#define maxn 1005

string S[maxn], T[maxn];

void solve(void) {
    int r, c, k;
    cin >> r >> c >> k;
    bool ans = true;
    for (int i = 1; i <= r; i++) {
        cin >> S[i] >> T[i];
        bool have = false;
        for (auto c : T[i]) have |= (c == '*');
        if (!have) continue;
        for (auto c : S[i])
            if (c == '-') ans = false;
    }
    cout << "NY"[ans] << endl;
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