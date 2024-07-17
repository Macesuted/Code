/**
 * @file 535265C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007

stack<int> S;

int main() {
    int q;
    cin >> q;

    int64_t ans = 0;
    while (q--) {
        int t, v;
        cin >> t >> v;
        while (t--) ans = (ans + mod - (int64_t)S.top() * S.size() % mod) % mod, S.pop();
        S.push(v), ans = (ans + (int64_t)S.top() * S.size() % mod) % mod;
        cout << ans << endl;
    }

    return 0;
}