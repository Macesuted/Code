/**
 * @file 105053D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-03
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

typedef pair<int, int> pii;

vector<pii> split;

void solve(void) {
    int64_t n;
    cin >> n;
    for (int64_t v = 2; v * v <= n; v++) {
        int cnt = 0;
        while (n % v == 0) cnt++, n /= v;
        if (cnt) split.emplace_back(cnt, v);
    }
    if (n > 1) split.emplace_back(1, n);
    if (split.size() == 1) return cout << "NY"[split[0].first % 2] << endl, void();
    if (split.size() == 2 && split[0].first == 1 && split[1].first == 1) return cout << 'Y' << endl, void();
    cout << 'N' << endl;
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