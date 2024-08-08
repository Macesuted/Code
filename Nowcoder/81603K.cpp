/**
 * @file 81603K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 500005

bool f[maxn];

void solve(void) {
    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;
    for (int i = 0; i <= n; i++) f[i] = false;
    f[0] = true;
    for (int i = 1; i < n; i++) {
        if (!f[i - 1]) continue;
        if (i + 2 <= n && s[i] == 'a' && s[i + 1] == 'v' && s[i + 2] == 'a') f[i + 2] = true;
        if (i + 4 <= n && s[i] == 'a' && s[i + 1] == 'v' && s[i + 2] == 'a' && s[i + 3] == 'v' && s[i + 4] == 'a')
            f[i + 4] = true;
    }
    cout << (f[n] ? "Yes" : "No") << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}