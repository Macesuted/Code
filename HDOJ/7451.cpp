/**
 * @file 7451.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) {
        string s;
        cin >> s;
        int n = s.size();
        s = ' ' + s;

        vector<int> pos;

        for (int i = 1; i <= n; i++)
            if (s[i] == '/') pos.push_back(i);
        for (int i = 1; i < pos[0] - 1; i++) cout << s[i];
        cout << endl;
        for (int i = 1; i + 1 < (int)pos.size(); i++) {
            string t;
            for (int j = pos[i] + 1; j < pos[i + 1]; j++) t.push_back(s[j]);
            int cnt = 0;
            for (int j = 1; j + 1 < (int)t.size(); j++)
                if (t[j] == '=') cnt++;
            if (i != 1 && cnt != 1) continue;
            cout << t << endl;
        }
    }
    return 0;
}