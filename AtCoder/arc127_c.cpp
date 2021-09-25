/**
 * @author Macesuted (macesuted@outlook.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define maxn 1000005

string s;
int n;

void minus1(void) {
    int p = n;
    while (s[p] == '0') p--;
    s[p] = '0';
    for (register int i = p + 1; i <= n; i++) s[i] = '1';
    return;
}

void work(void) {
    cin >> n;
    cin >> s;
    int t = s.size();
    s = ' ' + s;
    s.resize(n + 1);
    for (register int i = 0; i < t; i++) swap(s[n - i], s[t - i]);
    for (register int i = 1; i <= n - t; i++) s[i] = '0';
    int high = 1;
    cout << '1';
    minus1();
    for (register int i = 1; i <= n; i++) {
        while (high <= n && s[high] == '0') high++;
        if (high > n) break;
        if (s[i] == '1')
            cout << 1, s[i] = '0';
        else
            cout << 0, minus1();
    }
    cout << endl;
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(11);
    int _ = 1;
    // cin >> _;
    while (_--) work();
    return 0;
}