/**
 * @file 1023A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool mem1;

bool solve(void) {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    int p = -1;
    for (int i = 0; i < n; i++)
        if (s[i] == '*') p = i;
    if (p == -1) return s == t;
    if (n - 1 > m) return false;
    for (int i = 0; i < p; i++)
        if (s[i] != t[i]) return false;
    for (int i = n - 1, j = m - 1; i > p; i--, j--)
        if (s[i] != t[j]) return false;
    return true;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) cout << (solve() ? "YES" : "NO") << endl;

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
