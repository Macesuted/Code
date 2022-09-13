/**
 * @file 1729E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

int64_t query(int64_t a, int64_t b) {
    cout << "? " << a << ' ' << b << endl;
    int64_t t;
    cin >> t;
    return t;
}

void solve(void) {
    map<int64_t, int> cnt;
    for (int i = 2; i <= 26; i++) {
        int64_t r1 = query(1, i), r2 = query(i, 1);
        if (r1 == -1) return cout << "! " << i - 1 << endl, void();
        cnt[r1 + r2]++;
    }
    int maxCnt = 0;
    for (auto i : cnt) maxCnt = max(maxCnt, i.second);
    for (auto i : cnt)
        if (i.second == maxCnt) return cout << "! " << i.first << endl, void();
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