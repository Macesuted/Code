/**
 * @file 2760.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-08-12
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

typedef pair<int, int> pii;

class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        int pl, pr, pc, rnk, siz;
        bool res;
        Node(int pl_, int pr_, int pc_) { l = r = nullptr, pl = pl_, pr = pr_, pc = pc_, rnk = rand(), siz = 1, res = false; }
    };

    Node* root;
    int ccnt, fa[10000000];

    int getfa(int p) { return fa[p] == p ? p : fa[p] = getfa(fa[p]); }
    int getSiz(Node* p) { return p ? p->siz : 0; }
    void reset(Node* p) { return p ? (p->pc = ++ccnt, p->res = true, void()) : void(); }
    void pushDown(Node* p) { return p && p->res ? (reset(p->l), reset(p->r), p->res = false, void()) : void(); }
    void pushUp(Node* p) { return p->siz = 1 + getSiz(p->l) + getSiz(p->r), void(); }
    void splitl(Node* p, Node*& t1, Node*& t2, int pos) {
        if (!p) return t1 = t2 = nullptr, void();
        pushDown(p);
        if (p->pl < pos)
            t1 = p, splitl(p->r, t1->r, t2, pos);
        else
            t2 = p, splitl(p->l, t1, t2->l, pos);
        return pushUp(p);
    }
    void splitr(Node* p, Node*& t1, Node*& t2, int pos) {
        if (!p) return t1 = t2 = nullptr, void();
        pushDown(p);
        if (p->pr <= pos)
            t1 = p, splitr(p->r, t1->r, t2, pos);
        else
            t2 = p, splitr(p->l, t1, t2->l, pos);
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

   public:
    int64_t ans;

    FhqTreap(void) {
        root = new Node(INT_MIN, INT_MAX, 0), ccnt = 1, ans = 0;
        for (int i = 0; i < 10000000; i++) fa[i] = i;
    }
    void insertPoint(int v) {
        Node *pl = nullptr, *pc = nullptr, *pr = nullptr;
        splitl(root, pl, root, v), splitr(pl, pl, pc, v);
        pr = new Node(v, pc->pr, pc->pc), pc->pr = v;
        return merge(pc, pc, pr), merge(pl, pl, pc), merge(root, pl, root);
    }
    void erasePoint(int v) {
        Node *pl = nullptr, *ppl = nullptr, *ppr = nullptr;
        splitl(root, pl, root, v), splitr(pl, pl, ppl, v - 1), splitl(root, ppr, root, v + 1);
        assert(getSiz(ppl) == 1), assert(getSiz(ppr) == 1);
        if (getfa(ppl->pc) != getfa(ppr->pc)) ans--, fa[getfa(ppr->pc)] = getfa(ppl->pc);
        ppl->pr = ppr->pr, delete ppr;
        return merge(pl, pl, ppl), merge(root, pl, root);
    }
    void insertLine(int l, int r) {
        Node *pl = nullptr, *pc = nullptr;
        splitl(root, pl, root, l), splitr(root, pc, root, r);
        if (pc) reset(pc), ans += pc->siz;
        return merge(root, pc, root), merge(root, pl, root);
    }
} FHQ;

map<int, vector<pii>> rec;

void addP(int r, int c1, int c2) { return rec[c1].emplace_back(INT_MIN, r), rec[c2].emplace_back(INT_MAX, r), void(); }
void addL(int r1, int r2, int c) { return rec[c].emplace_back(r1, r2), void(); }

void solve(void) {
    int R, C, n;
    cin >> R >> C >> n;
    addP(0, 0, C), addP(R, 0, C), addL(0, R, 0), addL(0, R, C);
    for (int i = 1, r1, c1, r2, c2; i <= n; i++) {
        cin >> r1 >> c1 >> r2 >> c2;
        if (r1 == r2) addP(r1, c1, c2);
        if (c1 == c2) addL(r1, r2, c1);
    }
    for (auto& i : rec) {
        sort(i.second.begin(), i.second.end());
        for (auto j : i.second)
            if (j.first == INT_MIN)
                FHQ.insertPoint(j.second);
            else if (j.first == INT_MAX)
                FHQ.erasePoint(j.second);
            else
                FHQ.insertLine(j.first, j.second);
    }
    cout << FHQ.ans << endl;
    return;
}

bool mem2;

int main() {
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