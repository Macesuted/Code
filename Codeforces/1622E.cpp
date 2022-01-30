/**
 * @file 1622E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

#define maxn 10
#define maxm 10005

typedef pair<int, int> pii;

int a[maxn];
string s[maxn];
pii v[maxm];
int anp[maxm];

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> s[i];
    long long ans = -1;
    for (int S = 0; S < (1 << n); S++) {
        long long tot = 0;
        for (int i = 0; i < m; i++) v[i] = {0, i};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                if (s[i][j] == '1') v[j].first += (S >> i & 1) ? +1 : -1;
            tot += ((S >> i & 1) ? -1 : +1) * a[i];
        }
        sort(v, v + m);
        for (int i = 0; i < m; i++) tot += v[i].first * (i + 1);
        if (tot > ans) {
            ans = tot;
            for (int i = 0; i < m; i++) anp[v[i].second] = i + 1;
        }
    }
    for (int i = 0; i < m; i++) cout << anp[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
