/**
 * @file 2122C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-19
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

#define maxn 200005

using pii = pair<int, int>;

int a[maxn], b[maxn];
bool sa[maxn], sb[maxn];

void solve(void) {
    int n;
    cin >> n;
    vector<pii> va, vb;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i], va.emplace_back(a[i], i), vb.emplace_back(b[i], i);
    sort(va.begin(), va.end()), sort(vb.begin(), vb.end());
    for (int i = 0; i < n; i++) sa[va[i].second] = sb[vb[i].second] = i < n / 2;
    queue<int> S[4];
    for (int i = 1; i <= n; i++) S[sa[i] << 1 | sb[i]].push(i);
    assert(S[0].size() == S[3].size()), assert(S[1].size() == S[2].size());
    for (int t = 0; t < 2; t++)
        while (!S[t].empty()) {
            int p = S[t].front(), q = S[t ^ 3].front();
            S[t].pop(), S[t ^ 3].pop();
            cout << p << ' ' << q << endl;
        }
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