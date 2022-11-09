/**
 * @file S22054.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-04
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

#define mod 1000000007

int a[105];
int f[2][512][512];
set<int> SS;
vector<int> vS;

int Mod(int x) { return x >= mod ? x - mod : x; }
int Plus(int& x, int y) { return x = Mod(x + y); }

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    SS.clear(), SS.insert(511);
    for (int i = 1; i <= n; i++) {
        vector<int> cache;
        for (auto j : SS) cache.push_back(j & a[i]);
        for (auto j : cache) SS.insert(j);
    }
    vS.clear();
    for (auto i : SS) vS.push_back(i);
    for (int i = 1; i <= n; i++) {
        bool t = i & 1;
        f[t][a[i]][0] = 1, f[t][a[i]][511] = mod - 1;
        for (auto S : vS)
            for (int T = 0; T < 512; T++) {
                if (!f[!t][S][T]) continue;
                int v = f[!t][S][T];
                Plus(f[t][S][T], v);
                Plus(f[t][S & a[i]][T & a[i]], v);
                Plus(f[t][S & a[i]][(T & a[i]) | S], mod - v);
                f[!t][S][T] = 0;
            }
    }
    cout << f[n & 1][0][0] << endl;
    for (auto S : vS)
        for (int T = 0; T < 512; T++) f[n & 1][S][T] = 0;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("be.in", "r", stdin), freopen("be.out", "w", stdout);
#endif
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