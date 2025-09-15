/**
 * @file 11381.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-09-13
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

#define maxn 100005

using pii = pair<int, int>;

int a[maxn][3];

void solve(void) {
    int n;
    cin >> n;

    map<int, int> cnt0, cnt1, cnt2;
    map<pii, int> cnt01, cnt02, cnt12;
    for (int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        cnt0[a[i][0]]++;
        cnt1[a[i][1]]++;
        cnt2[a[i][2]]++;
        cnt01[{a[i][0], a[i][1]}]++;
        cnt02[{a[i][0], a[i][2]}]++;
        cnt12[{a[i][1], a[i][2]}]++;
    }

    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        int S0 = cnt0[a[i][0]] - 1, S1 = cnt1[a[i][1]] - 1, S2 = cnt2[a[i][2]] - 1;
        int S01 = cnt01[{a[i][0], a[i][1]}] - 1, S02 = cnt02[{a[i][0], a[i][2]}] - 1, S12 = cnt12[{a[i][1], a[i][2]}] - 1;
        S0 -= S01 + S02, S1 -= S01 + S12, S2 -= S02 + S12;
        ans += S0 * (S1 + S2 + S01 + S02 + S12);
        ans += S1 * (S2 + S01 + S02 + S12);
        ans += S2 * (S01 + S02 + S12);
        ans += S01 * (S01 - 1) / 2 + S01 * (S02 + S12);
        ans += S02 * (S02 - 1) / 2 + S02 * S12;
        ans += S12 * (S12 - 1) / 2;
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

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}