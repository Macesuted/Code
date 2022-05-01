/**
 * @file 1626B.cpp
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

void print(string &s, int p) {
    for (int i = 0; i + 1 < p; i++) cout << s[i];
    cout << s[p - 1] - '0' + s[p] - '0';
    for (int i = p + 1; i < s.size(); i++) cout << s[i];
    cout << endl;
    return;
}

void solve(void) {
    string a;
    cin >> a;
    bool poss = false;
    for (int i = 1; i < a.size(); i++)
        if (a[i] - '0' + a[i - 1] - '0' >= 10)
            poss = true;
    if (poss) {
        for (int i = a.size() - 1; i; i--)
            if (a[i] - '0' + a[i - 1] - '0' >= 10)
                return print(a, i);
    } else {
        for (int i = 1; i < a.size(); i++)
            if (a[i] != '0') return print(a, i);
    }
    return print(a, a.size() - 1);
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
