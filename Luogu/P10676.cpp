/**
 * @file P10676.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-06-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1005

int a[maxn];
multimap<double, int> S;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i], a[i]++;
        for (int j = 1; j < a[i]; j++) S.emplace((a[i] - 1.) / j, +1), S.emplace(double(a[i]) / j, -1);
    }
    int sum = 0;
    double ans = 1;
    for (auto [val, delt] : S) {
        if (delt == -1 && sum == n) ans = val;
        sum += delt;
    }
    cout << setiosflags(ios::fixed) << setprecision(6) << ans << endl;
    return;
}

bool mem2;

int main() {
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