/**
 * @file 247579.cpp
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

#define maxn 1000005

int lg2[maxn];

void solve(void) {
    int n, k, sum = 0;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) lg2[i] = lg2[i >> 1] + 1, sum += lg2[i - 1];
    if (k > sum) return cout << -1 << endl, void();
    vector<int> ans;
    for (int i = n; i; i--) {
        if (k >= lg2[i - 1]) {
            k -= lg2[i - 1], cout << i << ' ';
            continue;
        }
        if (!k) {
            for (int j = 1; j <= i; j++) cout << j << ' ';
        } else {
            int v = i - (1 << (k - 1));
            k = 0;
            for (int j = 1; j < v; j++) cout << j << ' ';
            cout << i << ' ';
            for (int j = v; j < i; j++) cout << j << ' ';
        }
        break;
    }
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