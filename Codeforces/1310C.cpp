/**
 * @file 1310C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1005

typedef pair<int, int> pii;

string s;
int n, m, lcp[maxn][maxn], id[maxn][maxn], rig[maxn];
int64_t k, f[maxn][maxn];
pii a[maxn * maxn];

int64_t check(int lim) {
    for (int i = 1; i <= n; i++) rig[i] = n + 1;
    for (int i = 1; i <= lim; i++) rig[a[i].first] = min(rig[a[i].first], a[i].second);
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = i; j < n; j++) f[i + 1][rig[j + 1]] = min(f[i + 1][rig[j + 1]] + f[i][j], k);
        for (int j = 1; j <= n; j++) f[i + 1][j] = min(f[i + 1][j - 1] + f[i + 1][j], k);
    }
    return f[m][n];
}

void solve(void) {
    cin >> n >> m >> k >> s, s = " " + s;
    for (int i = n; i; i--)
        for (int j = n; j; j--) lcp[i][j] = (s[i] == s[j] ? lcp[i + 1][j + 1] + 1 : 0);
    int tot = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) a[++tot] = {i, j};
    sort(a + 1, a + tot + 1, [&](pii a, pii b) {
        int lena = a.second - a.first + 1, lenb = b.second - b.first + 1, l = lcp[a.first][b.first];
        return l >= min(lena, lenb) ? (lena > lenb) : (s[a.first + l] > s[b.first + l]);
    });
    for (int i = 1; i <= tot; i++) id[a[i].first][a[i].second] = i;
    int l = 0, r = tot;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        (check(mid) < k ? l : r) = mid;
    }
    for (int i = a[r].first; i <= a[r].second; i++) cout << s[i];
    cout << endl;
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