/**
 * @file SXLK2022A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

map<string, string> def;
set<string> vis;

bool check(char c) { return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || c == '_'; }

string readName(stringstream& ssin) {
    string s;
    char c;
    while ((c = ssin.get()) && check(c)) s.push_back(c);
    return s;
}
void calc(string s) {
    string op;
    for (auto i : s) {
        if (check(i)) {
            op.push_back(i);
            continue;
        }
        if (!op.empty() && def.count(op) && !vis.count(op))
            vis.insert(op), calc(def[op]), vis.erase(op);
        else
            cout << op;
        op.clear(), cout << i;
    }
    if (!op.empty() && def.count(op) && !vis.count(op))
        vis.insert(op), calc(def[op]), vis.erase(op);
    else
        cout << op;
    return;
}

void solve(void) {
    int n;
    string s;
    cin >> n, getline(cin, s);
    for (int i = 1; i <= n; i++) {
        getline(cin, s);
        while (!s.empty() && (s.back() == '\n' || s.back() == '\r')) s.pop_back();
        if (!s.empty() && s[0] == '#') {
            stringstream ssin(s);
            ssin.get();
            if (readName(ssin) == "define") {
                string name = readName(ssin), content;
                getline(ssin, content), def[name] = content;
            } else
                def.erase(readName(ssin));
        } else
            calc(s);
        cout << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("preprocessor.in", "r", stdin), freopen("preprocessor.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}