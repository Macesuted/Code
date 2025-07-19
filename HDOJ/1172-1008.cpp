/**
 * @file 1172-1008.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-07-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

namespace FastIO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Ir = Ibuf, *Il = Ibuf;
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
int64_t read(void) {
    int64_t x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
}  // namespace FastIO
using FastIO::read;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        uint64_t xsum;
        Node(void) : l(nullptr), r(nullptr), xsum(0) {}
    };

    vector<Node*> root;
    int n;

    void pushUp(Node* p) {
        p->xsum = 0;
        if (p->l) p->xsum ^= p->l->xsum;
        if (p->r) p->xsum ^= p->r->xsum;
        return;
    }
    void update(Node*& p, int l, int r, int qp, uint64_t v) {
        p = new Node(p ? *p : Node());
        if (l == r) return p->xsum ^= v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p->l, l, mid, qp, v) : update(p->r, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void comp(Node* t1, Node* t2, int l, int r) {
        if (vals.size() > 70) return;
        uint64_t v1 = (t1 ? t1->xsum : 0), v2 = (t2 ? t2->xsum : 0);
        if (v1 == v2) return;
        if (l == r) {
            vals.insert(l);
            return;
        }
        int mid = (l + r) >> 1;
        comp(t1 ? t1->l : nullptr, t2 ? t2->l : nullptr, l, mid);
        comp(t1 ? t1->r : nullptr, t2 ? t2->r : nullptr, mid + 1, r);
        return;
    }

   public:
    void build(int _n, int a[], uint64_t v[]) {
        n = 1e9, root.push_back(new Node());
        for (int i = 1; i <= _n; i++) root.push_back(root.back()), update(root[i], 1, n, a[i], v[i]);
        return;
    }
    set<int> vals;
    void comp(int v1, int v2) { return vals.clear(), comp(root[v1], root[v2], 1, n); }
};

#define maxn 100005

int a[maxn];
uint64_t b[maxn];
bool S[70][70];
mt19937_64 rnd(5216342);

bool C(int n, int m) { return (n & m) == m; }

void solve(void) {
    int n = read();

    unordered_map<int, uint64_t> mp;
    unordered_map<uint64_t, int> rec;
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        if (!mp.count(a[i])) {
            mp[a[i]] = rnd();
            while (rec.count(mp[a[i]])) mp[a[i]] = rnd();
            rec[mp[a[i]]] = a[i];
        }
        b[i] = mp[a[i]];
    }

    SegmentTree SGT;
    SGT.build(n, a, b);

    int q = read();
    for (int i = 1, presum = 0; i <= q; i++) {
        int L = read(), R = read();
        int64_t k = read(), V = read();
        L ^= presum, R ^= presum, k ^= presum, V ^= presum;
        if (!(1 <= L && L <= R && R <= n)) continue;

        SGT.comp(L - 1, R);

        int cnt1 = __builtin_popcountll(k), cnt2 = SGT.vals.size();
        if (cnt1 < cnt2) {
            cout << 0 << endl;
            continue;
        }

        int mxv = 0;
        for (auto tv : SGT.vals) mxv = max(mxv, tv);
        if (mxv > V) {
            cout << 0 << endl;
            continue;
        }

        bool ans;
        if (k & 1)
            ans = ((S[cnt1 - 1][cnt2 + 1] & ((cnt2 + 1) & 1)) ^ S[cnt1 - 1][cnt2]) & ((V - cnt2) & 1);
        else
            ans = S[cnt1][cnt2];

        cout << ans << endl;
        presum += ans;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for (int cnt1 = 0; cnt1 < 70; cnt1++) {
        S[cnt1][0] = 0;
        for (int cnt2 = 1; cnt2 < cnt1; cnt2++) S[cnt1][cnt2] = S[cnt1 - 1][cnt2 - 1] ^ (S[cnt1 - 1][cnt2] & (cnt2 & 1));
        S[cnt1][cnt1] = 1;
    }

    int _ = read();
    while (_--) solve();

    return 0;
}
