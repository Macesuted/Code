/**
 * @file arc148_b.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-09-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

string s;

string reverse(int l, int r) {
    string t;
    for (int i = r; i >= l; i--) t.push_back(s[i] == 'd' ? 'p' : 'd');
    return t;
}

void solve(void) {
    int n;
    cin >> n >> s, s = " " + s;
    int l = 1;
    while (l <= n && s[l] == 'd') l++;
    if (l == n + 1) {
        for (int i = 1; i <= n; i++) cout << s[i];
        cout << endl;
        return;
    }
    string t = "z";
    for (int i = l; i <= n; i++) {
        string q = reverse(l, i);
        for (int j = i + 1; j <= n; j++) q.push_back(s[j]);
        t = min(t, q);
    }
    for (int i = 1; i < l; i++) cout << s[i];
    cout << t << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}