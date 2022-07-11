/**
 * @file 79.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-11
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

#define maxn 10
#define eps 1e-9

const double pi = acos(-1);

int d[maxn], p[maxn];

double solve(int n) {
    int minVal = 1e9;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) minVal = min(minVal, d[p[i]] * d[p[j]]);
    double l = -minVal, r = minVal;
    for (int _ = 60; _; _--) {
        double mid = (l + r) / 2, sum = 0;
        for (int i = 1; i <= n; i++) sum += acos(mid / d[p[i]] / d[p[i % n + 1]]);
        (sum < 2 * pi ? r : l) = mid;
    }
    if (fabs(l - minVal) < eps || fabs(l + minVal) < eps) return 0;
    double ans = 0;
    for (int i = 1; i <= n; i++) ans += sin(acos(l / d[p[i]] / d[p[i % n + 1]])) * d[p[i]] * d[p[i % n + 1]];
    return ans;
}
void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> d[i], p[i] = i;
    double ans = 0;
    do
        for (int i = 2; i <= n; i++) ans = max(ans, solve(i));
    while (next_permutation(p + 1, p + n + 1));
    cout << setprecision(10) << setiosflags(ios::fixed) << ans / 2 << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
#endif
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