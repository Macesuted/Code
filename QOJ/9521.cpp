/**
 * @file 9521.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

char c[15];
int w[15], d[15];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> d[i];
        if (c[i] == 'N')
            w[i] = 0;
        else if (c[i] == 'E')
            w[i] = 1;
        else if (c[i] == 'S')
            w[i] = 2;
        else
            w[i] = 3;
    }
    cout << 2 * n - 1 << ' ' << c[1] << endl;
    cout << "Z " << d[1] << endl;
    for (int i = 2; i <= n; i++) {
        cout << "LR"[w[i] == (w[i - 1] + 1) % 4] << endl;
        cout << "Z " << d[i] << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}