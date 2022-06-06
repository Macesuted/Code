/**
 * @file 1672H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-06
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

#define maxn 200005

string s;
int cnt[2][maxn];

void solve(void) {
    int n, q;
    cin >> n >> q >> s;
    s = " " + s;
    for (int i = 1; i < n; i++)
        if (s[i] == s[i + 1]) cnt[s[i] - '0'][i]++;
    for (int i = 1; i < n; i++) cnt[0][i] += cnt[0][i - 1], cnt[1][i] += cnt[1][i - 1];
    for (int i = 1, l, r; i <= q; i++)
        cin >> l >> r, cout << 1 + max(cnt[0][r - 1] - cnt[0][l - 1], cnt[1][r - 1] - cnt[1][l - 1]) << endl;
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