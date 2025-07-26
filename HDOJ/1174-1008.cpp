/**
 * @file 1174-1008.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 1000005

int a[maxn];

void solve(void) {
    int n;
    string s;
    cin >> n >> s;

    for (int i = 1; i <= n; i++) a[i] = (s[i - 1] - '0') ^ (i & 1);

    vector<int> rec;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        while (r + 1 <= n && a[l] == a[r + 1]) r++;
        rec.push_back(r - l + 1);
    }

    if (rec.size() == 1) return cout << 0 << endl, void();
    if (rec.size() & 1) rec.front() += rec.back(), rec.pop_back();
    int cur[2] = {0, 0};
    for (int i = 0; i < (int)rec.size(); i++) cur[i & 1] += (rec[i] + 1) / 2;
    cout << min(cur[0], cur[1]) << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}
