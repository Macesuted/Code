/**
 * @file 1625D.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

typedef pair<int, int> pii;

#define MP make_pair
#define MT make_tuple
#define maxn 300005
#define maxlgn 31

pii a[maxn];
int f[maxn], pre[maxn];

class Trie {
   private:
    struct Node {
        Node* son[2];
        pii val;
        Node(void) { son[0] = son[1] = NULL, val = {0, 0}; }
    };

    Node* root;

    void insert(Node*& p, int dep, int num, pii v) {
        if (p == NULL) p = new Node();
        p->val = max(p->val, v);
        if (~dep) insert(p->son[num >> dep & 1], dep - 1, num, v);
        return;
    }
    pii getMaxVal(Node* p, int dep, int num, int lim) {
        if (!~dep) return p->val;
        bool t = num >> dep & 1, lt = lim >> dep & 1;
        pii ans = {0, 0};
        if (!lt && p->son[t] != NULL) ans = max(ans, getMaxVal(p->son[t], dep - 1, num, lim));
        if (p->son[!t] != NULL) ans = max(ans, lt ? getMaxVal(p->son[!t], dep - 1, num, lim ^ (1 << dep)) : p->son[!t]->val);
        return ans;
    }

   public:
    Trie(void) { root = NULL; }
    void insert(int num, pii v) { return insert(root, maxlgn - 1, num, v); }
    pii getMaxVal(int num, int lim) { return root == NULL ? MP(0, 0) : getMaxVal(root, maxlgn - 1, num, lim); }
};

Trie TT;

void solve(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = i;
    sort(a + 1, a + n + 1);
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) {
        tie(f[i], pre[i]) = TT.getMaxVal(a[i].first, k);
        TT.insert(a[i].first, pii{++f[i], i});
    }
    int p = TT.getMaxVal(0, 0).second;
    if (f[p] < 2) return cout << -1 << endl, void();
    cout << f[p] << endl;
    static vector<int> ans;
    ans.clear();
    while (p != 0) ans.push_back(a[p].second), p = pre[p];
    sort(ans.begin(), ans.end());
    for (auto i : ans) cout << i << ' ';
    cout << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
