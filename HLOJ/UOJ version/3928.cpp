/**
 * @file 3928.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 45

typedef pair<int64_t, int> pii;

int64_t a[maxn], f[2][maxn][1 << 17], g[maxn];
int fail[maxn];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int64_t v = 0;
        for (auto j : s) v = (v << 1) | (j - '0');
        for (int i = m - 1; ~i; i--)
            if (v >> i & 1) {
                if (a[i])
                    v ^= a[i];
                else {
                    a[i] = v;
                    break;
                }
            }
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < i; j++)
            if (a[i] >> j & 1) a[i] ^= a[j];
    int L;
    cin >> L;
    string s;
    cin >> s;
    vector<pii> c;
    for (int i = 0; i < m; i++)
        if (a[i]) c.emplace_back(a[i], i);
    int cs = c.size();
    if (cs <= 22) {
        int64_t x = 0;
        for (auto i : s) x = (x << 1) | (i - '0');
        int64_t ans = 0;
        for (int S = 0; S < (1 << cs); S++) {
            int64_t v = 0;
            for (int i = 0; i < cs; i++)
                if (S >> i & 1) v ^= c[i].first;
            bool find = false;
            for (int j = 0; j + L - 1 <= m - 1 && !find; j++)
                if ((v >> j & ((1 << L) - 1)) == x) find = true;
            ans += find;
        }
        cout << (ans << (n - cs)) << endl;
    } else {
        s = " " + s;
        for (int i = 2; i <= L; i++) {
            fail[i] = fail[i - 1];
            while (fail[i] && s[fail[i] + 1] != s[i]) fail[i] = fail[fail[i]];
            fail[i] = fail[i] + (s[fail[i] + 1] == s[i]);
        }
        for (int i = 0; i < m; i++)
            if (a[i])
                for (int j = 0; j < m; j++)
                    if (!a[j]) g[i] = (g[i] << 1) | (a[i] >> j & 1);
        int64_t ans = 0;
        f[m & 1][0][0] = 1;
        for (int i = m - 1, cnt = 0; ~i; i--) {
            bool t = i & 1;
            if (a[i]) cnt++;
            for (int j = 0; j < L; j++)
                for (int S = 0; S < (1 << (m - cs)); S++) {
                    if (!f[!t][j][S]) continue;
                    if (a[i]) {
                        for (int c = 0; c < 2; c++) {
                            int p = j;
                            while (p && s[p + 1] - '0' != c) p = fail[p];
                            p += (s[p + 1] - '0' == c);
                            p == L ? ans += f[!t][j][S] << (n - cnt) : f[t][p][S ^ (c * g[i])] += f[!t][j][S];
                        }
                    } else {
                        int c = S >> (m - 1 - i - cnt) & 1, p = j;
                        while (p && s[p + 1] - '0' != c) p = fail[p];
                        p += (s[p + 1] - '0' == c);
                        p == L ? ans += f[!t][j][S] << (n - cnt) : f[t][p][S] += f[!t][j][S];
                    }
                    f[!t][j][S] = 0;
                }
        }
        cout << ans << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("xor.in", "r", stdin), freopen("xor.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
