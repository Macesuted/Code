/**
 * @file 6188.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-28
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

#define maxn 1000005

int rec[maxn];

void solve(void) {
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) rec[i] = 0;
        for (int i = 1, x; i <= n; i++) cin >> x, rec[x]++;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += rec[i] / 2;
            if (i + 2 <= n && rec[i] % 2 == 1 && rec[i + 1] % 2 == 1 && rec[i + 2] > 0)
                ans++, rec[i]--, rec[i + 1]--, rec[i + 2]--;
        }
        cout << ans << endl;
    }
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