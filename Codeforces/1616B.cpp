/**
 * @file 1616B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

void solve(void) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int p = 0;
    while (p + 1 < (int)s.size() && (s[p] > s[p + 1] || (s[p] == s[p + 1] && s[p] != s[0]))) p++;
    for (int i = 0; i <= p; i++) cout << s[i];
    for (int i = p; ~i; i--) cout << s[i];
    cout << endl;
    return;
}

bool mem2;

int main() {
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
