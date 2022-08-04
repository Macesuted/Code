/**
 * @file 1605A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-12-31
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

void solve(void) {
    string s, t;
    cin >> s >> t;
    int cnt[26];
    memset(cnt, 0, sizeof(cnt));
    for (auto i : s) cnt[i - 'a']++;
    if (t == "abc" && cnt[0]) {
        for (int i = 0; i < cnt[0]; i++) cout << 'a';
        for (int i = 0; i < cnt[2]; i++) cout << 'c';
        for (int i = 0; i < cnt[1]; i++) cout << 'b';
    } else {
        for (int i = 0; i < cnt[0]; i++) cout << 'a';
        for (int i = 0; i < cnt[1]; i++) cout << 'b';
        for (int i = 0; i < cnt[2]; i++) cout << 'c';
    }
    for (int i = 3; i < 26; i++)
        for (int j = 0; j < cnt[i]; j++) cout << char('a' + i);
    cout << endl;
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
