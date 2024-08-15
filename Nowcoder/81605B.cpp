/**
 * @file 81605B.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

struct Value {
    Value *son[2];
    int type;
    Value(void) { type = 0, son[0] = son[1] = nullptr; }

    void print(void) {
        if (type == 1) return cout << "int", void();
        if (type == 2) return cout << "double", void();
        cout << "pair<", son[0]->print(), cout << ',', son[1]->print(), cout << '>';
        return;
    }
};

map<string, Value *> vari;

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        string s, name, t;
        cin >> s >> name, name.pop_back();
        stack<Value *> S;
        queue<string> args;
        for (auto c : s) {
            if (c == '<' || c == ',' || c == '>') {
                if (!t.empty()) args.push(t), t.clear();
            } else
                t.push_back(c);
        }
        if (!t.empty()) args.push(t);
        while (!args.empty()) {
            string s = args.front();
            args.pop();
            Value *p = new Value();
            if (s == "int") p->type = 1;
            if (s == "double") p->type = 2;
            S.push(p);
            while (S.size() > 2) {
                Value *q = S.top();
                S.pop();
                Value *p = S.top();
                S.pop();
                if ((q->type || q->son[0]) && (p->type || p->son[0]))
                    S.top()->son[0] = p, S.top()->son[1] = q;
                else {
                    S.push(p), S.push(q);
                    break;
                }
            }
        }
        vari[name] = S.top();
    }
    for (int i = 1; i <= q; i++) {
        string s, t;
        cin >> s;
        queue<string> que;
        for (auto c : s)
            if (c == '.')
                que.push(t), t.clear();
            else
                t.push_back(c);
        que.push(t);
        Value *p = vari[que.front()];
        que.pop();
        while (!que.empty()) p = p->son[que.front() == "second"], que.pop();
        p->print(), cout << endl;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}