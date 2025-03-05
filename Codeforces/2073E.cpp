/**
 * @file 2073E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *child[2];
    int id;
    Node(int _id) { child[0] = child[1] = nullptr, id = _id; }
};

bitset<205> S;
int n;

bool query(void) {
    cout << "query ";
    for (int i = 0; i < n; i++) cout << S[i];
    cout << endl;
    int ret;
    cin >> ret;
    return ret;
}
void dfs(Node *p) {
    if (p->child[0] == nullptr) return cout.put('x'), void();
    return cout.put('('), dfs(p->child[0]), cout.put('-'), dfs(p->child[1]), cout.put(')'), void();
}

void solve(void) {
    cin >> n;

    stack<Node *> T;
    T.push(new Node(0)), S[0] = true;

    auto merge = [&](Node *x, Node *y) {
        if (!x) return y;
        if (!y) return x;
        Node *p = new Node(x->id);
        p->child[0] = x, p->child[1] = y;
        return p;
    };

    for (int i = 1; i < n; i++) {
        Node *p = T.top();
        T.pop(), S[p->id] = false;
        S[i] = true;

        bool tar = query();

        while (!T.empty() && (S[T.top()->id] = false, ((T.size() & 1) ^ tar) || query() == tar)) p = merge(T.top(), p), T.pop();
        if (!T.empty()) S[T.top()->id] = true;
        if (p) T.push(p), S[p->id] = true;
        T.push(new Node(i));
    }

    while (T.size() > 1) {
        Node *y = T.top();
        T.pop();
        Node *x = T.top();
        T.pop();
        T.push(merge(x, y));
    }

    cout << "answer ", dfs(T.top());

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}