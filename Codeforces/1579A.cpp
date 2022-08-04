/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

void work(void) {
    string s;
    cin >> s;
    int cnt[3] = {0, 0, 0};
    for (auto i : s) cnt[i - 'A']++;
    if (cnt[1] == cnt[0] + cnt[2])
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}