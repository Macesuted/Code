/**
 * @file 2107C.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-05
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

#define maxn 200005

int64_t a[maxn], ans[maxn];

void solve(void) {
    int n;
    int64_t tar;
    string s;
    cin >> n >> tar >> s, s = ' ' + s;
    for (int i = 1; i <= n; i++) cin >> a[i], ans[i] = a[i], a[i] += a[i - 1];

    auto getSum = [&](int l, int r) -> int64_t { return l > r ? 0 : a[r] - a[l - 1]; };
    auto print = [&](void) -> void {
        cout << "Yes" << endl;
        for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
        cout << endl;
        return;
    };

    vector<int> pos;
    pos.push_back(0);
    for (int i = 1; i <= n; i++)
        if (s[i] == '0') pos.push_back(i), ans[i] = -1e18;
    pos.push_back(n + 1);

    vector<int64_t> fr(pos.size()), fl(pos.size());
    int64_t oans = 0;
    for (int i = 1; i < (int)pos.size(); i++) {
        for (int j = pos[i - 1] + 1; j < pos[i]; j++)
            fr[i - 1] = max(fr[i - 1], getSum(pos[i - 1] + 1, j)), fl[i] = max(fl[i], getSum(j, pos[i] - 1));

        int64_t cur = 0;
        for (int j = pos[i - 1] + 1; j < pos[i]; j++) {
            cur += ans[j];
            if (cur < 0) cur = 0;
            oans = max(oans, cur);
        }
    }
    if (oans > tar) return cout << "No" << endl, void();
    if (oans == tar) return print();

    if (pos.size() == 2) return cout << "No" << endl, void();

    ans[pos[1]] = tar - fl[1] - fr[1];

    print();

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}