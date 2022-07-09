/**
 * @file 1458D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-09
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

#define maxn 500005

int edg[maxn << 1];

void solve(void) {
    string s;
    cin >> s;
    for (int i = 0, p = maxn; i < (int)s.size(); i++) s[i] == '0' ? edg[p++]++ : edg[--p]++;
    for (int p = maxn; edg[p - 1] || edg[p];)
        (edg[p] > 1 || (edg[p] && !edg[p - 1])) ? (cout << '0', edg[p++]--) : (cout << '1', edg[--p]--);
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
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}