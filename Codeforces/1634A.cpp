/**
 * @file 1634A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-17
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
    int n, k;
    string s;
    cin >> n >> k >> s;
    s = " " + s;
    if (k == 0) return cout << 1 << endl, void();
    bool check = true;
    for (int i = 1; i <= n; i++)
        if (s[i] != s[n - i + 1]) check = false;
    cout << 2 - int(check) << endl;
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
