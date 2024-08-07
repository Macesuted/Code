/**
 * @file 81602H.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef pair<int64_t, int64_t> pll;

const int64_t base1 = 1331, base2 = 13331, mod1 = 1e9 + 7, mod2 = 1e9 + 9;

list<vector<pll>> S;
map<string, int> key;
map<pll, string> dict;
int n;

pll getHash(string s) {
    pll v = {0, 0};
    for (auto c : s) v.first = (v.first * base1 + c) % mod1, v.second = (v.second * base2 + c) % mod2;
    dict[v] = s;
    return v;
}

int haveOut, deleteCnt;
vector<pll> solve(string s) {
    int m = s.size();
    vector<int> pos;
    for (int i = 0; i < m; i++)
        if (s[i] == '(' || s[i] == ')') pos.push_back(i);
    vector<string> args;
    int bl = pos.front(), br = pos.back();
    {
        string t;
        int cnt = 0;
        for (int i = bl + 1; i < br; i++) {
            char c = s[i];
            if (c == ',' && (pos.size() == 2 || i < pos[1]))
                args.push_back(t), t.clear(), cnt++;
            else
                t.push_back(c);
        }
        args.push_back(t);
    }
    string cmd = s.substr(0, bl);

    if (cmd == "begin") {
        return {};
    }
    if (cmd == "commit") {
        for (auto line = S.begin(); line != S.end(); line++) {
            if ((*line)[n].first == 1) (*line)[n].first = 0;
            if ((*line)[n].second == 1) line = S.erase(line), line--;
        }
        return {};
    }
    if (cmd == "abort") {
        for (auto line = S.begin(); line != S.end(); line++) {
            if ((*line)[n].second == 1) (*line)[n].second = 0;
            if ((*line)[n].first == 1) line = S.erase(line), line--;
        }
        return {};
    }

    set<pll> vals;

    if (cmd == "select_in") {
        cmd = "select";
        auto ret = solve(args[2]);
        for (auto i : ret) vals.insert(i);
    }
    if (cmd == "delete_in") {
        cmd = "delete";
        auto ret = solve(args[1]);
        for (auto i : ret) vals.insert(i);
    }
    if (cmd == "select") vals.insert(getHash(args[2]));
    if (cmd == "delete") vals.insert(getHash(args[1]));

    if (cmd == "insert") {
        vector<pll> line;
        line.reserve(n + 1);
        for (int i = 0; i < n; i++) line.push_back(getHash(args[i]));
        line.push_back({1, 0});
        S.push_back(line);
        return {};
    }
    if (cmd == "select") {
        haveOut = 1;
        vector<pll> ret;
        int out = key[args[0]], cond = key[args[1]];
        for (auto &line : S)
            if (line[n].second == 0 && vals.count(line[cond])) ret.push_back(line[out]);
        return ret;
    }
    if (cmd == "delete") {
        haveOut = 2, deleteCnt = 0;
        int cond = key[args[0]];
        for (auto &line : S)
            if (line[n].second == 0 && vals.count(line[cond])) line[n].second = 1, deleteCnt++;
        return {};
    }
    return {};
}

void solve(void) {
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        key[s] = i;
    }
    while (q--) {
        string command;
        cin >> command;
        haveOut = 0;
        vector<pll> ret = solve(command);
        if (haveOut == 1) {
            int x = ret.size();
            cout << x << endl;
            if (x) cout << dict[ret[1 - 1]] << endl << dict[ret[(x + 1) / 2 - 1]] << endl << dict[ret[x - 1]] << endl;
        } else if (haveOut == 2)
            cout << deleteCnt << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}