/**
 * @file 102268J.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-12
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

#define maxn 100005

int n, k, a[maxn];

bool check(int64_t lim, vector<int>& pos, int l, int r, int delt) {
    pos.clear();
    int64_t sum = 0;
    for (int i = l; i != r + delt; i += delt)
        if ((sum += a[i]) >= lim) sum = 0, pos.push_back(i);
    return (int)pos.size() >= k;
}

void solve(void) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int64_t l = 0, r = 5e9 + 1;
    vector<int> p1, p2;
    while (l + 1 < r) {
        int64_t mid = (l + r) / 2;
        (check(mid, p1, 1, n, +1) ? l : r) = mid;
    }
    check(l, p1, 1, n, +1);
    if ((int)p1.size() == k && p1.back() == n) {
        cout << "Yes" << endl;
        for (int i = 0; i < (int)p1.size() - 1; i++) cout << p1[i] << ' ';
        cout << endl;
        return;
    }
    check(r, p2, n, 1, -1);
    for (int i = 1; i <= k; i++)
        if (i - 1 < (int)p1.size() && k - i - 1 < (int)p2.size() && p1[i - 1] == p2[k - i - 1] - 1) {
            cout << "Yes" << endl;
            for (int j = 0; j < i; j++) cout << p1[j] << ' ';
            for (int j = k - i - 2; ~j; j--) cout << p2[j] - 1 << ' ';
            cout << endl;
            return;
        }
    cout << "No" << endl;
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