/**
 * @file 3536.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-06-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define mod 998244353

typedef pair<int, int> pii;

class Matrix {
   private:
    int64_t a[2][2];

   public:
    Matrix(void) { a[0][0] = a[1][1] = 1, a[0][1] = a[1][0] = 0; }
    Matrix(int64_t x) { a[0][0] = x, a[0][1] = a[1][0] = 1, a[1][1] = 0; }
    Matrix(int64_t x, int64_t y) { a[0][0] = x, a[1][0] = y, a[0][1] = a[1][1] = 0; }
    int64_t get(size_t x, size_t y) const { return a[x][y]; }
    int64_t* operator[](size_t x) { return a[x]; }
    Matrix operator*(const Matrix& o) const {
        Matrix ans;
        ans[0][0] = (get(0, 0) * o.get(0, 0) + get(0, 1) * o.get(1, 0)) % mod;
        ans[0][1] = (get(0, 0) * o.get(0, 1) + get(0, 1) * o.get(1, 1)) % mod;
        ans[1][0] = (get(1, 0) * o.get(0, 0) + get(1, 1) * o.get(1, 0)) % mod;
        ans[1][1] = (get(1, 0) * o.get(0, 1) + get(1, 1) * o.get(1, 1)) % mod;
        return ans;
    }
};

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int rnk, siz, val;
        bool fli, rev, col;
        Matrix lM, rM;
        void set(int x) { return lM = rM = Matrix(siz = val = x), void(); }
        Node(int x, bool c) { l = r = nullptr, rnk = rand(), fli = rev = false, col = c, set(x); }
    };

    Node* root;

    int getSiz(Node* p) { return p ? p->siz : 0; }
    void flip(Node* p) { return p ? p->col ^= true, p->fli ^= true, void() : void(); }
    void reverse(Node* p) { return p ? swap(p->l, p->r), swap(p->lM, p->rM), p->rev ^= true, void() : void(); }
    void pushDown(Node* p) {
        if (!p) return;
        if (p->fli) flip(p->l), flip(p->r), p->fli = false;
        if (p->rev) reverse(p->l), reverse(p->r), p->rev = false;
        return;
    }
    void pushUp(Node* p) {
        if (!p) return;
        p->lM = p->rM = Matrix(p->siz = p->val);
        if (p->l) p->siz += p->l->siz, p->lM = p->lM * p->l->lM, p->rM = p->l->rM * p->rM;
        if (p->r) p->siz += p->r->siz, p->lM = p->r->lM * p->lM, p->rM = p->rM * p->r->rM;
        return;
    }
    void split(Node* p, Node*& t1, Node*& t2, int siz) {
        if (!p) return t1 = t2 = nullptr, void();
        pushDown(p);
        if (p->val + getSiz(p->l) <= siz)
            t1 = p, split(p->r, t1->r, t2, siz - p->val - getSiz(p->l));
        else
            t2 = p, split(p->l, t1, t2->l, siz);
        return pushUp(p);
    }
    void splitLef(Node* p, Node*& t1, Node*& t2) {
        if (!p) return t1 = t2 = nullptr, void();
        pushDown(p);
        if (!p->l)
            t2 = p->r, t1 = p, p->r = nullptr;
        else
            t2 = p, splitLef(p->l, t1, t2->l);
        return pushUp(p);
    }
    void splitRig(Node* p, Node*& t1, Node*& t2) {
        if (!p) return t1 = t2 = nullptr, void();
        pushDown(p);
        if (p->r)
            t1 = p, splitRig(p->r, t1->r, t2);
        else
            t1 = p->l, t2 = p, p->l = nullptr;
        return pushUp(p);
    }
    void merge(Node*& p, Node* t1, Node* t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        if (t1->rnk < t2->rnk)
            pushDown(p = t1), merge(p->r, t1->r, t2);
        else
            pushDown(p = t2), merge(p->l, t1, t2->l);
        return pushUp(p);
    }
    void cMerge(Node*& l, Node*& r) {
        Node *p = nullptr, *q = nullptr;
        splitRig(l, l, p), splitLef(r, q, r);
        if (p && q && p->col == q->col) p->set(p->val + q->val), delete q, q = nullptr;
        return merge(l, l, p), merge(l, l, q), merge(l, l, r);
    };
    void cut(Node*& pl, Node*& pc, Node*& pr, int l, int r) {
        pl = pc = pr = nullptr;
        split(root, pl, pc, l - 1);
        if (getSiz(pl) != l - 1) {
            Node* p = nullptr;
            int t = l - 1 - getSiz(pl);
            splitLef(pc, p, pc), merge(pl, pl, new Node(t, p->col)), p->set(p->val - t), merge(pc, p, pc);
        }
        split(pc, pc, pr, r - l + 1);
        if (getSiz(pc) != r - l + 1) {
            Node* p = nullptr;
            int t = r - l + 1 - getSiz(pc);
            splitLef(pr, p, pr), merge(pc, pc, new Node(t, p->col)), p->set(p->val - t), merge(pr, p, pr);
        }
        return;
    }

   public:
    FhqTreap(void) { root = nullptr; }
    void init(string s) {
        for (auto l = s.begin(), r = l; l != s.end(); l = r) {
            while (r != s.end() && *l == *r) r++;
            merge(root, root, new Node(r - l, *l == 'W'));
        }
        return;
    }
    void append(char c) {
        int tc = (c == 'W');
        Node* p = nullptr;
        splitRig(root, root, p);
        if (p->col == tc)
            p->set(p->val + 1);
        else
            merge(p, p, new Node(1, tc));
        return merge(root, root, p);
    }
    void flip(int l, int r) {
        Node *pl = nullptr, *pc = nullptr, *pr = nullptr;
        cut(pl, pc, pr, l, r), flip(pc);
        root = pl, cMerge(root, pc), cMerge(root, pr);
        return;
    }
    void reverse(int l, int r) {
        Node *pl = nullptr, *pc = nullptr, *pr = nullptr;
        return cut(pl, pc, pr, l, r), reverse(pc), root = pl, cMerge(root, pc), cMerge(root, pr);
    }
    pii getAns(void) {
        Node* p = nullptr;
        splitRig(root, root, p);
        Matrix ans = (p->col ? Matrix(p->val + 1, 1) : p->rM * Matrix(1, 1));
        if (root) ans = root->rM * ans;
        merge(root, root, p);
        pii ret = {ans[0][0], ans[1][0]};
        p = nullptr, splitLef(root, p, root);
        if (p->col) swap(ret.first, ret.second);
        merge(root, p, root);
        return ret;
    }
};

FhqTreap FT;

void solve(void) {
    int n, q;
    string s;
    cin >> n >> q >> s;
    FT.init(s);
    auto x = FT.getAns();
    cout << x.first << ' ' << x.second << endl;
    while (q--) {
        string op;
        cin >> op;
        if (op == "APPEND") {
            char c;
            cin >> c;
            FT.append(c);
        } else if (op == "FLIP") {
            int l, r;
            cin >> l >> r;
            FT.flip(l, r);
        } else {
            int l, r;
            cin >> l >> r;
            FT.reverse(l, r);
        }
        auto x = FT.getAns();
        cout << x.first << ' ' << x.second << endl;
    }
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("code.in", "r", stdin), freopen("code.out", "w", stdout);
#endif
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