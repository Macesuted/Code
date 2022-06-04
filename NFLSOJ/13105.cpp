/**
 * @file 13105.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-04
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

#define maxn 22

int a[1 << maxn], cnt = 0;

void dfs(int p, int d, int c) {
    vector<int> lchain, rchain;
    lchain.push_back(p), rchain.push_back(p);
    for (int i = 1; i <= d; i++) lchain.push_back(lchain.back() << 1), rchain.push_back(rchain.back() << 1 | 1);
    a[lchain.back()] = a[rchain.back()] = c, lchain.pop_back(), rchain.pop_back();
    a[p] = a[lchain.back()] = a[rchain.back()] = ++cnt;
    if (lchain.back() != p) a[lchain.back() << 1 | 1] = a[rchain.back() << 1] = cnt;
    for (int i = 1, j = d - 2; i <= j; i++, j--) {
        int x = ++cnt;
        a[lchain[i]] = a[rchain[i]] = x, dfs(lchain[i] << 1 | 1, d - i - 1, x), dfs(rchain[i] << 1, d - i - 1, x);
        if (i == j) continue;
        a[lchain[j]] = a[rchain[j]] = x, dfs(lchain[j] << 1 | 1, d - j - 1, x), dfs(rchain[j] << 1, d - j - 1, x);
    }
    return;
}

void solve(void) {
    int n, k;
    cin >> n >> k;
    if (n == 1) return cout << "1\n1 1 1" << endl, void();
    dfs(1, n, ++cnt);
    cout << cnt << endl;
    for (int i = 1; i < (1 << (n + 1)); i++) cout << a[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef LOCAL
    freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
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