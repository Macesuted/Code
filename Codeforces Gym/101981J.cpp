/**
 * @file 101981J.cpp
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

#define maxn 1000005

vector<int> prime;
bool notPrime[maxn];
map<int, vector<int>> pos;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, v; i <= n; i++) {
        cin >> v;
        for (auto j : prime) {
            if (j * j > v) break;
            if (v % j != 0) continue;
            while (v % j == 0) v /= j;
            pos[j].push_back(i);
        }
        if (v > 1) pos[v].push_back(i);
    }
    int64_t ans = 0;
    for (auto &[i, vec] : pos) {
        int q = 1;
        for (auto p : vec) ans += (int64_t)(p - q + 1) * (n - p + 1), q = p + 1;
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxn; i++) {
        if (!notPrime[i]) prime.push_back(i);
        for (auto j = prime.begin(); j != prime.end() && i * *j < maxn; j++) {
            notPrime[i * *j] = true;
            if (i % *j == 0) break;
        }
    }

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}