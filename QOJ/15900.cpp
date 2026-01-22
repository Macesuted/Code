/**
 * @file 15900.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-01-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

multiset<int> split(int n) {
    multiset<int> S;
    for (int i = 2; i * i <= n; i++)
        while (n % i == 0) S.insert(i), n /= i;
    if (n > 1) S.insert(n);
    return S;
}

void solve(void) {
    int w, h, d, n;
    cin >> w >> h >> d >> n;

    multiset<int> Sw = split(w), Sh = split(h), Sn = split(n);

    int wc = 1, hc = 1, dc = 1;
    for (auto i = Sn.begin(); i != Sn.end();)
        if (Sw.count(*i))
            Sw.erase(Sw.find(*i)), wc *= *i, i = Sn.erase(i);
        else
            i++;
    for (auto i = Sn.begin(); i != Sn.end();)
        if (Sh.count(*i))
            Sh.erase(Sh.find(*i)), hc *= *i, i = Sn.erase(i);
        else
            i++;
    dc = n / wc / hc;

    if (d % dc) return cout << -1 << endl, void();

    cout << wc - 1 << ' ' << hc - 1 << ' ' << dc - 1 << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
