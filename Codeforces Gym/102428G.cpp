/**
 * @file 102428G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 200005

class StringAutomaton {
   private:
    struct Node {
        Node *son[26], *link;
        int len;
        Node(void) { memset(son, 0, sizeof(son)), link = nullptr, len = 0; }
    };

    Node *root, *last;

   public:
    StringAutomaton(void) { root = last = new Node(); }
    void pushBack(char c) {
        int v = c - 'A';
        auto p = last, np = new Node();
        np->len = p->len + 1;
        while (p && !p->son[v]) p->son[v] = np, p = p->link;
        if (!p)
            np->link = root;
        else {
            auto q = p->son[v];
            if (p->len + 1 == q->len)
                np->link = q;
            else {
                auto t = new Node();
                *t = *q, t->len = p->len + 1;
                while (p && p->son[v] == q) p->son[v] = t, p = p->link;
                np->link = q->link = t;
            }
        }
        last = np;
        return;
    }
    int solve(string s) {
        queue<int> que;
        for (auto c : s) que.push(c - 'A');
        int ans = 0;
        while (!que.empty()) {
            ans++;
            bool work = false;
            auto p = root;
            while (!que.empty() && p->son[que.front()]) p = p->son[que.front()], que.pop(), work = true;
            if (!work) return -1;
        }
        return ans;
    }
} SAM;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    string s;
    cin >> s;
    for (auto c : s) SAM.pushBack(c);

    int q;
    cin >> q;
    while (q--) cin >> s, cout << SAM.solve(s) << endl;

    return 0;
}