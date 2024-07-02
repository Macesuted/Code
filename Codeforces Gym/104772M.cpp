/**
 * @file 104772M.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

void solve(void) {
    string s, t;
    cin >> s >> t;
    for (auto &i : s)
        if ('A' <= i && i <= 'Z') i = i - 'A' + 'a';
    for (auto &i : t)
        if ('A' <= i && i <= 'Z') i = i - 'A' + 'a';
    int j = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        while (j < (int)t.size() && s[i] != t[j])
            if (t[j] == 'a' || t[j] == 'e' || t[j] == 'i' || t[j] == 'o' || t[j] == 'u' || t[j] == 'y')
                j++;
            else
                return cout << "Different" << endl, void();
        if (j == (int)t.size()) return cout << "Different" << endl, void();
        j++;
    }
    while (j != (int)t.size())
        if (t[j] == 'a' || t[j] == 'e' || t[j] == 'i' || t[j] == 'o' || t[j] == 'u' || t[j] == 'y')
            j++;
        else
            return cout << "Different" << endl, void();
    cout << "Same" << endl;
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