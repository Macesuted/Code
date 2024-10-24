/**
 * @file 9484.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 50005

int a[maxn], f[2][maxn];
queue<int> S[2];

bool query(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    char c;
    cin >> c;
    return c == 'B';
}

void solve(void) {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int x = query(1, i);
        f[x][i] = 1, S[x].push(i);
    }
    while (!S[0].empty() && !S[1].empty()) {
        int p = S[0].front(), q = S[1].front(), x = query(p, q);
        if (!x)
            S[1].pop(), f[x][q] = p;
        else
            S[0].pop(), f[x][p] = q;
    }
    int x = (S[0].empty() ? 1 : 0);
    cout << "!" << endl;
    for (int i = 2; i <= n; i++) cout << f[x][i] << ' ' << i << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}