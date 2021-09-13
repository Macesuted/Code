/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

string str;

void work(void) {
    cin >> str;
    int n = str.size();
    str = "1" + str;
    int cnt = 0;
    for (register int i = 1; i <= n; i++)
        if (str[i] == '0' && str[i - 1] == '1') cnt++;
    cout << min(2LL, cnt) << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    cin >> _;
    while (_--) work();
    return 0;
}