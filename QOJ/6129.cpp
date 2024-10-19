/**
 * @file 6129.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-10-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

int s[maxn], a[maxn], b[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    string sss;
    cin >> sss;
    int len = sss.size();
    for (int i = 1; i <= len; i++) s[i] = sss[i - 1] - '0';
    for (a[1] = 1; a[1] <= 9; a[1]++) {
        bool chk = true;
        int p = 1;
        for (int j = 1; j <= m && chk; j++)
            if (p <= len && s[p] % a[1] == 0)
                b[j] = s[p] / a[1], p++;
            else if (p + 1 <= len && (s[p] * 10 + s[p + 1]) % a[1] == 0 && (s[p] * 10 + s[p + 1]) / a[1] < 10)
                b[j] = (s[p] * 10 + s[p + 1]) / a[1], p += 2;
            else
                chk = false;
        if (!chk) continue;
        for (int i = 2; i <= n && chk; i++) {
            a[i] = -1;
            for (int j = 1; j <= m && chk; j++) {
                if (!b[j]) {
                    if (p <= len && s[p] == 0)
                        p++;
                    else
                        chk = false;
                    continue;
                }
                int v = -1;
                if (p <= len && s[p] % b[j] == 0)
                    v = s[p] / b[j], p++;
                else if (p + 1 <= len && (s[p] * 10 + s[p + 1]) % b[j] == 0 && (s[p] * 10 + s[p + 1]) / b[j] < 10)
                    v = (s[p] * 10 + s[p + 1]) / b[j], p += 2;
                else
                    chk = false;
                if (a[i] == -1) a[i] = v;
                if (a[i] != v) chk = false;
            }
        }
        if (!chk || p != len + 1) continue;
        for (int i = 1; i <= n; i++) cout << a[i];
        cout << ' ';
        for (int i = 1; i <= m; i++) cout << b[i];
        cout << endl;
        return;
    }
    cout << "Impossible" << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}