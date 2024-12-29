/**
 * @file 2053C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-28
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

typedef pair<int64_t, int64_t> pll;

pll dfs(int64_t n, int64_t k) {
    if (n < k) return {0, 0};
    int64_t m = n >> 1;
    pll ret = dfs(n >> 1, k);
    pll ans = {ret.first * 2 + ret.second * (n - m), ret.second * 2};
    if (n & 1) ans.first += m + 1, ans.second++;
    return ans;
}

void solve(void) {
    int64_t n, k;
    cin >> n >> k;
    cout << dfs(n, k).first << endl;
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