/**
 * @file 105053K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005

int f[maxn][3];

bool isVowel(char c) { return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y'; }

void solve(void) {
    int n;
    cin >> n;
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        int l = 0, r = 0;
        bool pre = true;
        for (int j = 0; j < min(3, (int)s.size()); j++) {
            if (isVowel(s[j]))
                pre = false, r = 0;
            else {
                if (pre) l++;
                r++;
            }
            if (pre)
                for (int x = 0; x + j + 1 < 3; x++) f[i][x + j + 1] = min(f[i][x + j + 1], f[i - 1][x] + j + 1);
            else
                for (int x = 0; x + l < 3; x++) f[i][r] = min(f[i][r], f[i - 1][x] + j + 1);
        }
    }
    int64_t v = min({f[n][0], f[n][1], f[n][2]});
    if (v == 0x3f3f3f3f)
        cout << '*' << endl;
    else
        cout << v << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}