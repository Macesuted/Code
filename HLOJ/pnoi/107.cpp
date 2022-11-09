/**
 * @file 107.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-10-26
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

#define maxn 100005

int a[maxn], b[maxn];
double c[maxn];
int n, k;

bool check(double lim) {
    for (int i = 1; i <= n; i++) c[i] = a[i] - b[i] * lim;
    sort(c + 1, c + n + 1, greater<>());
    double sum = 0;
    for (int i = 1; i <= k; i++) sum += c[i];
    return sum >= 0;
}

void solve(void) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    double l = 0, r = 1;
    while (abs(r - l) > 1e-6) {
        double mid = (l + r) / 2;
        (check(mid) ? l : r) = mid;
    }
    cout << setprecision(8) << fixed << l << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("salt.in", "r", stdin), freopen("salt.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}