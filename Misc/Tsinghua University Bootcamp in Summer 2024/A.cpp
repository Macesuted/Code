/**
 * @file A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

void solve(void) {
    int64_t S = ((int64_t)1 << 32) - 1;

    cout << "? " << 0 << endl;
    int64_t s1, s2;
    cin >> s1;
    cout << "? " << S << endl;
    cin >> s2;
    cout << "! " << s1 + s2 - 2 * S << endl;
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
