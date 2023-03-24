/**
 * @file 1809D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    string s;
    cin >> s;
    while (!s.empty() && s.back() == '1') s.pop_back();
    reverse(s.begin(), s.end());
    while (!s.empty() && s.back() == '0') s.pop_back();
    reverse(s.begin(), s.end());
    int64_t cur = 0;
    for (auto i : s) cur += (i == '0') * 1000000000001;
    int64_t ans = cur;
    for (int i = 0, j; i < (int)s.size(); i = j + 1) {
        j = i;
        while (j + 1 < (int)s.size() && s[j + 1] == '0') j++;
        ans = min(ans, cur - (j - i)), cur -= (j - i - 1) * 1000000000001;
    }
    cout << min(ans, cur) << endl;
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