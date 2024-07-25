/**
 * @file 102428K.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

vector<int64_t> a, ans;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;

    for (int i = 1; i < n; i++)
        if (s[i] != s[i + 1]) a.push_back(i * 2 + 1);

    ans.push_back(s.back() == 'H' ? +1 : -1);
    for (auto i : a) {
        ans.push_back(0);
        for (int j = (int)ans.size() - 2; ~j; j--) ans[j + 1] -= ans[j] * i;
    }

    cout << ans.size() - 1 << endl;
    for (auto i : ans) cout << i << ' ';
    cout << endl;

    return 0;
}