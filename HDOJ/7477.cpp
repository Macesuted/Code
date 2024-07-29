/**
 * @file 7477.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 1000005

string S;

int nxt[maxn][40], pre[maxn][40];
int f[maxn];

int code(char c) { return '0' <= c && c <= '9' ? c - '0' : c - 'a' + 10; }

void solve(void) {
    int n, m;
    cin >> n >> m;
    cin >> S, S = ' ' + S;
    for (int i = 1; i <= m; i++) f[i] = 0;

    for (int j = 0; j < 40; j++) nxt[m][j] = nxt[m + 1][j] = m + 1;
    for (int i = m - 1; ~i; i--) {
        for (int j = 0; j < 40; j++) nxt[i][j] = nxt[i + 1][j];
        nxt[i][code(S[i + 1])] = i + 1;
    }

    for (int j = 0; j < 40; j++) pre[1][j] = pre[0][j] = 0;
    for (int i = 2; i <= m + 1; i++) {
        for (int j = 0; j < 40; j++) pre[i][j] = pre[i - 1][j];
        pre[i][code(S[i - 1])] = i - 1;
    }

    for (int i = 1; i <= 12; i++) {
        int day = 30;
        if (i == 2) day = 29;
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) day = 31;
        for (int j = 1; j <= day; j++) {
            string s = "0000";
            int mon = i, day = j;
            s[1] = mon % 10 + '0', s[0] = mon / 10 % 10 + '0';
            s[3] = day % 10 + '0', s[2] = day / 10 + '0';
            int p = m + 1;
            for (int t = 3; ~t; t--) p = pre[p][code(s[t])];
            f[p]++;
        }
    }

    for (int i = m - 1; i; i--) f[i] += f[i + 1];

    int64_t ans = 0;
    while (n--) {
        string s;
        cin >> s;
        int p = 0;
        for (char c : s) p = nxt[p][code(c)];
        if (p < m) ans += f[p + 1];
    }
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}