/**
 * @file 1626A.cpp
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

int cnt[26];

void solve(void) {
    string s;
    cin >> s;
    memset(cnt, 0, sizeof(cnt));
    for (auto i : s) cnt[i - 'a']++;
    for (int i = 0; i < 26; i++)
        if (cnt[i] == 2) cout << char('a' + i);
    for (int i = 0; i < 26; i++)
        if (cnt[i] == 1) cout << char('a' + i);
    for (int i = 0; i < 26; i++)
        if (cnt[i] == 2) cout << char('a' + i);
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
