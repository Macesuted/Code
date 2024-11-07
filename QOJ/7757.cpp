/**
 * @file 7757.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-11-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

void solve(void) {
    int n;
    cin >> n;

    vector<int> a(n + 1), pos(n + 1);

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x; i <= n; i++) cin >> x, pos[x] = i;
    for (int i = 1; i <= n; i++) a[i] = pos[a[i]];

    string ans;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++)
            if (a[j] > a[j + 1])
                ans.push_back('2'), swap(a[j], a[j + 1]);
            else
                ans.push_back('1');
        ans.push_back('1');
    }
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}