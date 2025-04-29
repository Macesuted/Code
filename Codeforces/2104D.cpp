/**
 * @file 2104D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-04-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxv 8000005
#define maxn 400005

bool notp[maxv];
vector<int> prime;
int64_t sum[maxn];
int a[maxn];

void solve(void) {
    int n;
    cin >> n;
    int64_t tot = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], tot += a[i];
    sort(a + 1, a + n + 1);
    int ans = 0;
    while (ans < n - 1 && tot < sum[n - ans]) tot -= a[++ans];
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxv; i++) {
        if (!notp[i]) prime.push_back(i);
        for (auto j = prime.begin(); i * *j < maxv; j++) {
            notp[i * *j] = true;
            if (i % *j == 0) break;
        }
    }

    for (int i = 1; i < maxn; i++) sum[i] = sum[i - 1] + prime[i - 1];

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}