/**
 * @file 212.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-22
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

#define maxv 1000005

int64_t prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89};

void solve(void) {
    int N = 500;
    vector<int64_t> ans = {2, 3, 2};
    int t = 2;
    while ((int)ans.size() < N) {
        int n = ans.size();
        for (int i = n - 2; ~i; i--) ans.push_back(ans[i]);
        for (int i = 0; i < n - 1; i += 2) ans[i] *= prime[t], ans[2 * n - i - 2] *= prime[t + 1];
        for (int i = 1; i < n - 1; i += 2) ans[i] *= prime[t + 1], ans[2 * n - i - 2] *= prime[t];
        t += 2;
    }
    cout << N << endl;
    for (int i = 0; i < N; i++) cout << ans[i] << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("output.in", "r", stdin), freopen("output.out", "w", stdout);
#endif
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