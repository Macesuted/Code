/**
 * @file arc136_e.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-11-10
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

#define maxn 1000005

int f[maxn];
int64_t sum[maxn];
bool notp[maxn];
vector<int> prime;

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        int l = i, r = i;
        if (i == 1)
            l = 1, r = n;
        else if (i & 1)
            l = i - f[i] + 1, r = i + f[i] - 1;
        sum[max(1, l)] += x, sum[min(n, r) + 1] -= x;
    }
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, sum[i] += sum[i - 1]);
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
        if (!notp[i]) prime.push_back(i), f[i] = i;
        for (auto j = prime.begin(); i * *j < maxn; j++) {
            notp[i * *j] = true, f[i * *j] = *j;
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