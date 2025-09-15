/**
 * @file 11373.cpp
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

#define maxn 1000005

int a[maxn], ppcnt[1 << 10], sumj[1 << 10];

void solve(void) {
    int n, m;
    int64_t A, B;
    cin >> n >> m >> A >> B;

    const int U = (1 << m) - 1;

    vector<int> rec[1 << 10];
    vector<int64_t> prei[1 << 10];
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) a[i] |= (s[j] - '0') << j;
        if (a[i] & 1) a[i] ^= U;
        rec[a[i]].push_back(i);
    }

    auto calc = [&](int S, int i) -> int64_t { return ppcnt[S] * i * A + sumj[S] * B; };

    for (int T = 0; T < (1 << m); T++) {
        if (rec[T].empty()) continue;
        prei[T].resize(rec[T].size());
        prei[T][0] = rec[T][0];
        for (int i = 1; i < (int)rec[T].size(); i++) prei[T][i] = prei[T][i - 1] + rec[T][i];
    }

    int64_t ans = INT64_MIN;
    for (int S = 0; S < (1 << m); S++) {
        int64_t sum = 0;
        for (int T = 0; T < (1 << m); T++) {
            if (rec[T].empty()) continue;
            int o = calc(T ^ S, rec[T][0]) > calc(T ^ S ^ U, rec[T][0]) ? T ^ S : T ^ S ^ U;
            int l = 0, r = rec[T].size();
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                (calc(o, rec[T][mid]) > calc(o ^ U, rec[T][mid]) ? l : r) = mid;
            }
            sum += A * ppcnt[o] * prei[T][l] + B * sumj[o] * (l + 1);
            sum += A * ppcnt[o ^ U] * (prei[T].back() - prei[T][l]) + B * sumj[o ^ U] * (rec[T].size() - l - 1);
        }
        ans = max(ans, sum);
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

    for (int S = 0; S < (1 << 10); S++)
        for (int i = 0; i < 10; i++)
            if (S >> i & 1) sumj[S] += i + 1, ppcnt[S]++;

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}