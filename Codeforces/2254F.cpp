/**
 * @file 2254F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-08-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

int a[maxn], b[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    int lst = 0;
    for (int i = 1; i <= n; i++) lst ^= a[i] ^ b[i];

    for (int i = 1; i <= n; i++) b[i] ^= lst;

    map<int, int> ideg, odeg;
    ideg[0]++, odeg[lst]++;
    for (int i = 1; i <= n; i++) ideg[a[i]]++, odeg[b[i]]++;

    for (auto [p, v] : ideg)
        if (v != odeg[p]) return cout << "NO" << endl, void();

    cout << "YES" << endl;

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
