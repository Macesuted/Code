/**
 * @file 10122.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-03-13
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

class Trie {
   private:
    struct Node {
        Node *son[2];
        vector<int> S;
        Node(void) { son[0] = son[1] = nullptr; }
    };

    Node *root;

    int get(Node *&p, const vector<bool> &s, int b) {
        if (b == (int)s.size()) {
            if (p->S.empty()) return -1;
            int v = p->S.back();
            p->S.pop_back();
            return v;
        }
        if (!p->son[s[b]]) return -1;
        return get(p->son[s[b]], s, b + 1);
    }
    void put(Node *&p, const vector<bool> &s, int b, int v) {
        if (b == (int)s.size()) return p->S.push_back(v);
        if (!p->son[s[b]]) p->son[s[b]] = new Node();
        return put(p->son[s[b]], s, b + 1, v);
    }

   public:
    Trie(void) { root = new Node(); }

    int get(const vector<bool> &s) { return get(root, s, 0); }
    void put(const vector<bool> &s, int v) { return put(root, s, 0, v); }
} TR;

void solve(void) {
    int n, m;
    cin >> n >> m;

    vector<vector<bool>> a(m, vector<bool>(n));

    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) a[i][j] = s[j] - '0';
    }

    for (int j = n - 1; ~j; j--) {
        vector<bool> S(m - 1);
        for (int i = 1; i < m; i++) S[i - 1] = a[i][j];
        TR.put(S, j + 1);
    }

    vector<int> ans(n);

    for (int j = 0; j < n; j++) {
        vector<bool> S(m - 1);
        for (int i = 0; i < m - 1; i++) S[i] = a[i][j];
        ans[j] = TR.get(S);
        if (ans[j] == -1) return cout << "NO" << endl, void();
    }

    cout << "YES" << endl;
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    cout << endl;

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
