/**
 * @file L.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> dict;

const string str[4][10] = {{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
                           {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
                           {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
                           {"", "M", "MM", "MMM"}};
const string ca[7] = {"I", "V", "X", "L", "C", "D", "M"};

string word[4000];
bool sg[4000];
int fa[4000];

void solve(void) {
    for (int i = 1; i < 4000; i++)
        dict[word[i] = str[3][i / 1000 % 10] + str[2][i / 100 % 10] + str[1][i / 10 % 10] + str[0][i % 10]] = i;

    vector<string> rec;
    for (auto &[s, v] : dict) rec.push_back(s);
    sort(rec.begin(), rec.end(), [&](const string &a, const string &b) { return a.size() > b.size(); });
    for (auto &s : rec) {
        int p = dict[s];
        sg[p] = false;
        for (int t = 0; t < 7 && !sg[p]; t++) {
            string ss = ca[t] + s;
            if (dict.count(ss) && !sg[dict[ss]]) sg[p] = true, fa[p] = dict[ss];
            ss = s + ca[t];
            if (dict.count(ss) && !sg[dict[ss]]) sg[p] = true, fa[p] = dict[ss];
        }
    }
    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        int p = dict[s], turn = 2 - sg[p];
        cout << turn << endl;
        while (true) {
            if (turn == 1)
                cout << word[p = fa[p]] << endl;
            else {
                string t;
                cin >> t;
                if (t == "GG") break;
                p = dict[t];
            }
            turn = 3 - turn;
        }
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}