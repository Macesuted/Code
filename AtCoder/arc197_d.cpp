/**
 * @file arc197_d.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-04
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

#define maxn 405
#define mod 998244353

using pSS = pair<bitset<maxn>, bitset<maxn>>;

pSS S[maxn];
int fa[maxn];
bitset<maxn> faS[maxn];
int64_t fac[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        S[i].first.reset(), S[i].second.reset();
        for (int j = 1, v; j <= n; j++) cin >> v, S[i].first[j] = v;
        S[i].second[i] = 1;
    }

    if ((int)S[1].first.count() != n) return cout << 0 << endl, void();

    int tn = n;
    n = 0;
    for (int i = 1; i <= tn; i++) {
        bool fnd = false;
        for (int j = 1; j <= n && !fnd; j++)
            if (S[i].first == S[j].first) fnd = true, S[j].second |= S[i].second;
        if (!fnd) S[++n] = S[i];
    }

    sort(S + 1, S + n + 1, [](const pSS& a, const pSS& b) { return a.first.count() > b.first.count(); });

    int64_t ans = fac[S[1].second.count() - 1];
    for (int i = 2; i <= n; i++) ans = ans * fac[S[i].second.count()] % mod;

    faS[1] = S[1].second;
    for (int i = 2; i <= n; i++) {
        fa[i] = i - 1;
        while ((S[fa[i]].first & S[i].first) != S[i].first) fa[i]--;
        faS[i] = faS[fa[i]] | S[i].second;
    }
    for (int i = n; i; i--) {
        if (i > 1) S[fa[i]].second |= S[i].second;
        if (S[i].first != (S[i].second | faS[i])) return cout << 0 << endl, void();
    }

    cout << ans << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}