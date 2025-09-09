/**
 * @file 2138C2.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-08
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

int fa[maxn], dep[maxn], cnt[maxn];
bool leaf[maxn];

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cnt[i] = 0, leaf[i] = true;

    dep[1] = 1;
    for (int i = 2; i <= n; i++) cin >> fa[i], dep[i] = dep[fa[i]] + 1, leaf[fa[i]] = false;

    int mndep = n;
    for (int i = 1; i <= n; i++) {
        cnt[dep[i]]++;
        if (leaf[i]) mndep = min(mndep, dep[i]);
    }

    bitset<maxn> S, T;
    S[0] = 1;
    int ans = 0, delt = n, l = 0;
    for (int i = 0; i <= k; i++) T[i] = 1;

    while ((S & T).count() && ans < mndep) {
        ans++, delt -= cnt[ans];
        S |= S << cnt[ans];
        while (k - delt > l) T[l++] = 0;
    }

    if (!(S & T).count()) ans--;

    cout << ans << endl;

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