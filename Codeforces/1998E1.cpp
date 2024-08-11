/**
 * @file 1998E1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 200005

typedef pair<int, int> pii;

int a[maxn];
int64_t sum[maxn];
bool f[maxn];
pii rec[maxn];
set<int> S;


void solve(void) {
    int n, x;
    cin >> n >> x;
    for (int i = 1; i <= n; i++) cin >> a[i], rec[i] = {a[i], i}, f[i] = false, sum[i] = sum[i - 1] + a[i];
    sort(rec + 1, rec + n + 1, greater<pii>());
    S.clear(), S.insert(0), S.insert(n + 1);
    for (int i = 1; i <= n; i++) {
        int p = rec[i].second;
        int pl = *--S.lower_bound(p), pr = *S.lower_bound(p);
        S.insert(p);
        if (pl == 0 && pr == n + 1) {
            f[p] = true;
            continue;
        }
        int64_t v = sum[pr - 1] - sum[pl];
        if (pl != 0 && f[pl] && v >= a[pl]) f[p] = true;
        if (pr != n + 1 && f[pr] && v >= a[pr]) f[p] = true;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += f[i];
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