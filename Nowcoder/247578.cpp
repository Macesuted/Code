/**
 * @file 247578.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-06
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

bool solve(void) {
    int64_t a, b;
    cin >> a >> b;
    if (a == b) return a % 3 == 2;
    return min(a, b) % 3 != 0;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) cout << (solve() ? "niuniu" : "niumei") << endl;

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}