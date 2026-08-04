/**
 * @file 2254D.cpp
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

int64_t a[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    map<int64_t, int64_t> val, rval;
    for (int i = 1; i <= n; i++) val[a[i]]++;

    if (val.begin()->first != 0) return cout << -1 << endl, void();

    for (auto p = val.begin(), q = next(p); q != val.end(); p = q++) {
        if ((q->first - p->first) % p->second != 0) return cout << -1 << endl, void();
        rval[p->first] = (q->first - p->first) / p->second;
    }

    rval[val.rbegin()->first] = 1;
    if (val.size() > 1) rval[val.rbegin()->first] += rval[next(val.rbegin())->first];

    for (auto p = rval.begin(), q = next(p); q != rval.end(); p = q++)
        if (p->second >= q->second) return cout << -1 << endl, void();

    for (int i = 1; i <= n; i++) cout << rval[a[i]] << ' ';
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
