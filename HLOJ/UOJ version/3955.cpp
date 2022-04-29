/**
 * @file ant.cpp
 * @author Macesuted Moe (i@macesuted.moe)
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

int pos[maxn], p[maxn], rk[maxn], id[maxn], ans[maxn];
bool way[maxn];
vector<int> S[2];

void solve(void) {
    int n, m;
    int64_t t;
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        cin >> pos[i], p[i] = pos[i];
        char c;
        cin >> c;
        S[way[i] = (c == 'R')].push_back(pos[i]);
    }
    sort(S[0].begin(), S[0].end()), sort(S[1].begin(), S[1].end()), sort(p, p + n);
    for (int i = 0; i < n; i++) id[rk[i] = lower_bound(p, p + n, pos[i]) - p] = i;
    auto cnt = [&](int64_t l, int64_t r, bool k) {
        int64_t x = l / m;
        l -= x * m, r -= x * m;
        if (l < 0) l += m, r += m;
        if (r < m) return upper_bound(S[k].begin(), S[k].end(), r) - lower_bound(S[k].begin(), S[k].end(), l);
        return (S[k].end() - lower_bound(S[k].begin(), S[k].end(), l)) + 
               (r / m - 1) * (int64_t)S[k].size() + (upper_bound(S[k].begin(), S[k].end(), r % m) - S[k].begin());
    };
    for (int i = 0; i < n; i++)
        if (way[i])
            ans[id[(rk[i] + cnt(pos[i], pos[i] + 2 * t, 0)) % n]] = (pos[i] + t) % m;
        else
            ans[id[(rk[i] + n - cnt(pos[i] - 2 * t, pos[i], 1) % n) % n]] = (pos[i] + m - t % m) % m;
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("ant.in", "r", stdin), freopen("ant.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}