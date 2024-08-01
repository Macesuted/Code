/**
 * @file 81601H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 1000005

int a[maxn], pre[maxn][10];
vector<int> pos;

bool solve(void) {
    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;
    for (int i = 1; i <= n; i++)
        if (s[i] == 'U')
            a[i] = 6;
        else
            a[i] = s[i] - '0';
    for (int i = 1; i <= n; i++) {
        for (int j = 3; j <= 6; j++) pre[i][j] = pre[i - 1][j];
        pre[i][a[i]]++;
    }
    pos.clear();
    for (int i = 1; i <= n; i++)
        if (a[i] > 4) pos.push_back(i);

    for (int l = 1, r = 10; r <= n; l++, r++)
        if (pre[r][3] - pre[l - 1][3] == 10) return false;
    for (int l = 1, r = 90; r <= n; l++, r++)
        if (pre[r][5] - pre[l - 1][5] == 0 && pre[r][6] - pre[l - 1][6] == 0) return false;
    for (int i = 1; i < (int)pos.size(); i++) {
        int l = pos[i - 1], r = pos[i];
        if (a[l] == 5 && a[r] == 5) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "valid" : "invalid") << endl;

    return 0;
}