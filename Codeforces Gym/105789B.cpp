/**
 * @file 105789B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

using bs = bitset<1505>;

bs base[1505], ids[1505];
bool vis[1505];
int n, m;

void insert(int id, bs v) {
    bs cid;
    cid.set(id);
    for (int i = 0; i <= m; i++) {
        if (!v[i]) continue;
        if (!vis[i]) {
            base[i] = v, ids[i] = cid, vis[i] = true;
            return;
        }
        v ^= base[i], cid ^= ids[i];
    }
    int c = cid.count() / 2;
    for (int b = 1, p = 0; b <= n; b++) p += cid[b], cout << (cid[b] ? (1 + (p > c)) : 0);
    cout << endl;
    exit(0);
}

void solve(void) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        bs v;
        v.set(0);
        for (int j = 0; j < m; j++) v[j + 1] = s[j] - '0';
        insert(i, v);
    }
    cout << '*' << endl;
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