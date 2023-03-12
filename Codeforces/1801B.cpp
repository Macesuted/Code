/**
 * @file 1801B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 500005

typedef pair<int, int> pii;

pii a[maxn];
int f[maxn];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1);
    f[n + 1] = INT_MIN;
    for (int i = n; i; i--) f[i] = max(f[i + 1], a[i].second);
    set<int> S;
    S.insert(INT_MIN), S.insert(INT_MAX);
    int ans = INT_MAX;
    for (int i = 1, j; i <= n; i = j + 1) {
        j = i;
        while (j < n && a[j + 1].first == a[i].first) j++;
        if (i < j)
            for (int k = i; k <= j; k++) S.insert(a[k].second);
        int p = a[i].first, q = f[j + 1];
        if (q < p) q = max(q, *--S.upper_bound(p));
        if (q != INT_MIN) ans = min(ans, abs(p - q));
        if (q < p) ans = min(ans, *S.upper_bound(p) - p);
        if (i == j) S.insert(a[i].second);
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

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}