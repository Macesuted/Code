/**
 * @file 2824.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-31
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

int64_t val = 0;

int64_t solve(vector<int> a, bool zero = true) {
    bool chk = true;
    for (auto i : a) chk &= (i == 0);
    if (chk) return zero;
    if (a.size() == 1) {
        int64_t num = 0;
        for (int i = 1, cnt = 0; i < 10; i++)
            if (a[0] >> i & 1) {
                num = num * 10 + i;
                if (!cnt++ && (a[0] & 1)) num = num * 10;
            }
        if (!num && (a[0] & 1)) num = 10;
        if (!num && zero) num = 1;
        return num;
    }
    int64_t ans = INT64_MAX;
    for (int i = 0, cnt; i < 10; i++) {
        vector<int> b;
        cnt = i - 1, b.push_back(0);
        for (auto j : a) {
            cnt++;
            if (cnt == 10) cnt = 0, b.push_back(0);
            b.back() |= j ^ ((j >> cnt & 1) << cnt);
        }
        if (a == b) continue;
        val = val * 10 + i;
        ans = min(ans, solve(b, i == 0 && (a[0] & 1)) * 10 + i);
        val /= 10;
    }
    return ans;
}

void solve(void) {
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 0, t; i < n; i++) cin >> t, a.push_back(1 << t);
    cout << solve(a) << endl;
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