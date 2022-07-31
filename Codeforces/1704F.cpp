/**
 * @file 1704F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-31
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

int sg[34] = {8, 1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 9, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4};

int getSg(int x) {
    if (x == 0 || x == 14 || x == 34) return 0;
    if (x == 16 || x == 17 || x == 31 || x == 51) return 2;
    return sg[x % 34];
}

void solve(void) {
    int n;
    string s;
    cin >> n >> s;
    int cnt[2] = {0, 0};
    for (int i = 0; i < n; i++) cnt[s[i] == 'B']++;
    if (cnt[0] != cnt[1]) return cout << (cnt[0] > cnt[1] ? "Alice" : "Bob") << endl, void();
    int ans = 0;
    for (int l = 0, r; l < n; l = r + 1) {
        r = l;
        while (r + 1 < n && s[r + 1] != s[r]) r++;
        ans ^= getSg(r - l);
    }
    cout << (ans ? "Alice" : "Bob") << endl;
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