/**
 * @file 1352G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-25
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
    cin >> n;
    if (n <= 3) return cout << -1 << endl, void();
    if (n == 4) return cout << "3 1 4 2" << endl, void();
    if (n == 5) return cout << "1 4 2 5 3" << endl, void();
    vector<int> odd, even;
    odd.push_back(0), even.push_back(0);
    for (int i = 1; i <= n; i += 2) odd.push_back(i);
    for (int i = 2; i <= n; i += 2) even.push_back(i);
    int on = odd.size() - 1, en = even.size() - 1;
    for (int i = 1; i <= on; i++) cout << odd[i] << ' ';
    if (n & 1) {
        cout << even[en - 1] << ' ' << even[en] << ' ' << even[en - 2];
        en = en - 3;
    } else {
        cout << even[en - 2] << ' ' << even[en] << ' ' << even[en - 1];
        en = en - 3;
    }
    for (int i = en; i; i--) cout << ' ' << even[i];
    cout << endl;
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
