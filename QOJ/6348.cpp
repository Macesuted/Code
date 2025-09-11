/**
 * @file 6348.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 500005

int64_t a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    if (n > 80) {
        vector<int> pos;
        for (int i = 1; i < n; i++)
            if (a[i + 1] / a[i] == 1) pos.push_back(i++);
        cout << "YES" << endl;
        cout << pos[0] << ' ' << pos[0] + 1 << ' ' << pos[1] << ' ' << pos[1] + 1 << endl;
        return;
    }

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            for (int p = j + 1; p <= n; p++)
                for (int q = p + 1; q <= n; q++)
                    if (a[j] / a[i] == a[q] / a[p]) {
                        cout << "YES" << endl;
                        cout << i << ' ' << j << ' ' << p << ' ' << q << endl;
                        return;
                    }

    cout << "NO" << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
