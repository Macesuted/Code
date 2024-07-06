/**
 * @file 101981A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-04
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

bool solve(void) {
    int n, m;
    cin >> n >> m;
    if (n == 0) return 0;
    if (m == 1) return n % 2;
    return 1;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) cout << (solve() ? "Adrien" : "Austin") << endl;

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}