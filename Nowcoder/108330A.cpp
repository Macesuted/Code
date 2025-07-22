/**
 * @file 108330A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1500

int f[maxn], a[maxn][maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> f[i];
    for (int i = 1; i <= n; i++) {
        queue<int> que;
        for (int j = 0; j < i; j++) que.push(j + (j >= f[i]));
        for (int j = 1; j <= i; j++) {
            if (que.front() == f[j]) que.push(que.front()), que.pop();
            assert(que.front() != f[j]);
            a[i][j] = a[j][i] = que.front(), que.pop();
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << a[i][j] << ' ';
        cout << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
