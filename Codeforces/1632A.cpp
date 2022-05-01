/**
 * @file 1632A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

void solve(void) {
    int n;
    string s;
    cin >> n >> s;
    int cnt[2] = {0, 0};
    for (auto i : s) cnt[i - '0']++;
    if (cnt[0] >= 2 || cnt[1] >= 2)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
