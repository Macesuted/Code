/**
 * @file 696681E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2026-06-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

int64_t fib[60], ori[40], base[40], idx[40];

void solve(void) {
    int64_t n, m;
    cin >> n >> m;

    fib[0] = fib[1] = 1;
    for (int i = 2; i < 59; i++) fib[i] = fib[i - 2] + fib[i - 1];

    vector<int64_t> rest;
    for (int i = 0; i < 59; i++) {
        int64_t v = fib[i], id = 0;
        for (int j = 0; j < 40; j++) {
            if (!(v >> j & 1)) continue;
            if (!idx[j]) {
                ori[j] = fib[i], base[j] = v, idx[j] = id ^ ((int64_t)1 << j);
                break;
            }
            v ^= base[j], id ^= idx[j];
        }
        if (!v) rest.push_back(fib[i]);
    }

    int ans = INT_MAX;
    for (size_t S = 0; S < (1 << rest.size()); S++) {
        int64_t xsum = 0, sum = 0;
        for (size_t i = 0; i < rest.size(); i++)
            if (S >> i & 1) xsum ^= rest[i], sum += rest[i];

        int64_t v = n ^ xsum, id = 0;
        for (int i = 0; i < 40; i++)
            if (v >> i & 1) v ^= base[i], id ^= idx[i];
        for (int i = 0; i < 40; i++)
            if (id >> i & 1) sum += ori[i];

        if (sum > m || (m - sum) & 1) continue;

        int cur = __builtin_popcountll(id) + __builtin_popcountll(S);
        for (int i = 58; ~i; i--)
            if (sum + 2 * fib[i] <= m) sum += 2 * fib[i], cur += 2;
        ans = min(ans, cur);
    }

    cout << (ans == INT_MAX ? -1 : ans) << endl;

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
