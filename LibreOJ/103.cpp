/**
 * @file 103.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 1000005

int nxt[maxn];

void solve(void) {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    nxt[0] = -1;
    for (int i = 1; i < m; i++) {
        nxt[i] = nxt[i - 1];
        while (~nxt[i] && b[nxt[i] + 1] != b[i]) nxt[i] = nxt[nxt[i]];
        nxt[i] += (b[nxt[i] + 1] == b[i]);
    }
    int cnt = 0;
    for (int i = 0, p = -1; i < n; i++) {
        while (~p && a[i] != b[p + 1]) p = nxt[p];
        p += (a[i] == b[p + 1]);
        if (p == m - 1) cnt++, p = nxt[p];
    }
    cout << cnt << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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