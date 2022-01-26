/**
 * @file arc132_d.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 300005

typedef pair<int, int> pii;

string s, t;
int p[maxn];
int f[maxn][2];

void solve(void) {
    int n, m;
    cin >> n >> m >> s >> t;
    s = " " + s, t = " " + t;
    int len = n + m;
    for (int i = 1, j = 1; i <= len; i++)
        if (s[i] == '1') {
            while (t[j] != '1') j++;
            p[i] = j++;
        }
    for (int i = 1, j = 1; i <= len; i++)
        if (s[i] == '0') {
            while (t[j] != '0') j++;
            p[i] = j++;
        }

    int cnt0 = 1, cnt1 = 1;
    for (int opt = 0, i = 1, j = 1, x = 1; x <= len; opt = !opt, cnt0++) {
        while (i <= len && s[i] != '0') i++;
        while (j <= len && s[j] != '1') j++;
        if (!opt) {
            while (i <= len && min(i, p[i]) <= x && x <= max(i, p[i])) {
                i++, x++;
                while (i <= len && s[i] != '0') i++;
            }
        } else {
            while (j <= len && min(j, p[j]) <= x && x <= max(j, p[j])) {
                j++, x++;
                while (j <= len && s[j] != '1') j++;
            }
        }
    }
    for (int opt = 1, i = 1, j = 1, x = 1; x <= len; opt = !opt, cnt1++) {
        while (i <= len && s[i] != '0') i++;
        while (j <= len && s[j] != '1') j++;
        if (!opt) {
            while (i <= len && min(i, p[i]) <= x && x <= max(i, p[i])) {
                i++, x++;
                while (i <= len && s[i] != '0') i++;
            }
        } else {
            while (j <= len && min(j, p[j]) <= x && x <= max(j, p[j])) {
                j++, x++;
                while (j <= len && s[j] != '1') j++;
            }
        }
    }
    cout << len - min(cnt0, cnt1) + 1 << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
