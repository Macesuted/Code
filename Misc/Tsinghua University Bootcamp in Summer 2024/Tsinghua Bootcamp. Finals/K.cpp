/**
 * @file K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int st[10];
int64_t ans[10][10];

void solve(void) {
    for (int i = 1; i <= 9; i++)
        for (int j = 0; j <= 9; j++) ans[i][j] = -1;
    for (int64_t v = 1; v <= 1e4; v++) {
        int64_t tl = 0, val = v * v;
        while (val) st[tl++] = val % 10, val /= 10;
        if (ans[st[tl - 1]][st[0]] == -1) ans[st[tl - 1]][st[0]] = v * v;
    }
    int a, b;
    cin >> a >> b;
    cout << ans[a][b] << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}