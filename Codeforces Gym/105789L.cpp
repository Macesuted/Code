/**
 * @file 105789L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

const string nums[10] = {"GGGgGGG", "gggggGG", "gGGGGGg", "ggGGGGG", "GggGgGG",
                         "GgGGGgG", "GGGGGgG", "ggGggGG", "GGGGGGG", "GgGGGGG"};

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        vector<int> might;
        for (int v = 0; v < 10; v++) {
            bool chk = true;
            for (int j = 0; j < 7; j++)
                if (s[j] == 'g' || s[j] == 'G') chk &= (s[j] == nums[v][j]);
            if (chk) might.push_back(v);
        }
        if (might.size() > 1)
            cout << '*';
        else
            cout << might.front();
    }
    cout << endl;
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