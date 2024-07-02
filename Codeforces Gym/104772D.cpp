/**
 * @file 104772D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-02
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

int gcd(int x, int y) { return x ? gcd(y % x, x) : y; }

void solve(void) {
    int n;
    cin >> n;
    int sum = 0, tn = n;
    while (tn) sum += tn % 10, tn /= 10;
    int lcm = sum / gcd(sum, n) * n;
    for (int i = lcm / sum; i; i--) cout << n;
    cout << endl;
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