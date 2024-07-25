/**
 * @file 102428E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

string s;
vector<int> a;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin >> s;
    int n = s.size(), m;
    cin >> m;

    for (int i = 0; i < n; i++)
        if (s[i] == 'E') a.push_back(i);
    int len = a.size();
    for (int i = 0; i < len; i++) a.push_back(a[i] + n);
    for (int i = 0; i < len; i++) a.push_back(a[i] + 2 * n);

    int64_t ans = 0;
    for (int i = len; i < 2 * len; i++) {
        int l = a[i] - a[i - 1], c = min(l, m);
        ans += int64_t(m + (m - c + 1)) * c / 2;
    }
    cout << ans << endl;
    return 0;
}