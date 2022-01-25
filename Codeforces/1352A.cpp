/**
 * @file 1352A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

bool mem1;

void solve(void) {
    string s;
    cin >> s;
    vector<int> ans;
    for (int i = s.size() - 1, base = 1; ~i; i--, base *= 10) {
        if (s[i] == '0') continue;
        ans.push_back((s[i] - '0') * base);
    }
    cout << ans.size() << endl;
    for (auto i : ans) cout << i << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
