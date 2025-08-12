/**
 * @file 1179-1011.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define maxn 3005
#define maxq 100005

namespace FastIO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf;
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
string readString(void) {
    string s;
    s.reserve(50);
    char c = getch();
    while (c != ' ' && c != '\n' && c != '\r') s.push_back(c), c = getch();
    return s;
}
}  // namespace FastIO
using namespace FastIO;

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;
using tiiii = tuple<int, int, int, int>;

mt19937 rnd(114514);
class FhqTreap {
   private:
    struct Node {
        Node *l, *r;
        tiii val;
        int rnk, siz;
        Node(tiii v) { l = r = nullptr, val = v, rnk = rnd(), siz = 1; }
    };

    Node *root;

    int getSiz(Node *p) { return p ? p->siz : 0; }
    void pushUp(Node *p) { return p->siz = 1 + getSiz(p->l) + getSiz(p->r), void(); }
    void splitV(Node *p, Node *&t1, Node *&t2, tiii v) {
        if (!p) return t1 = t2 = nullptr, void();
        if (p->val <= v)
            t1 = p, splitV(p->r, t1->r, t2, v);
        else
            t2 = p, splitV(p->l, t1, t2->l, v);
        return pushUp(p);
    }
    void splitS(Node *p, Node *&t1, Node *&t2, int siz) {
        if (!p) return t1 = t2 = nullptr, void();
        if (1 + getSiz(p->l) <= siz)
            t1 = p, splitS(p->r, t1->r, t2, siz - 1 - getSiz(p->l));
        else
            t2 = p, splitS(p->l, t1, t2->l, siz);
        return pushUp(p);
    }
    void merge(Node *&p, Node *t1, Node *t2) {
        if (!t1) return p = t2, void();
        if (!t2) return p = t1, void();
        if (t1->rnk < t2->rnk)
            p = t1, merge(p->r, t1->r, t2);
        else
            p = t2, merge(p->l, t1, t2->l);
        return pushUp(p);
    }

   public:
    FhqTreap(void) { root = nullptr; }
    void insert(tiii v) {
        Node *tr = nullptr;
        splitV(root, root, tr, v);
        merge(root, root, new Node(v)), merge(root, root, tr);
        return;
    }
    void erase(tiii v) {
        Node *tc = nullptr, *tr = nullptr;
        splitV(root, root, tr, v), splitS(root, root, tc, getSiz(root) - 1);
        delete tc;
        merge(root, root, tr);
        return;
    }
    int getRnk(tiii v) {
        Node *tr = nullptr;
        splitV(root, root, tr, v);
        int ret = getSiz(tr) + 1;
        merge(root, root, tr);
        return ret;
    }
};

unordered_map<string, int> rec;
string host[maxn];
tiii val[maxn];
int id[maxn];
set<tiii> cmp[maxn][maxn];
tiiii ccmp[maxq];

void solve(void) {
    int n = read(), q = read();

    rec.clear();
    for (int i = 1; i <= 3 * n; i++) {
        for (int x = 0; x < 6; x++) {
            string s = readString();
            rec[s] = i;
            if (!x) host[i] = s;
        }
        id[i] = read();
    }

    FhqTreap FT[4];

    for (int t = 1; t <= 3; t++) {
        vector<pair<string, int>> names;
        names.reserve(n);
        for (int i = 1; i <= 3 * n; i++)
            if (id[i] == t) names.emplace_back(host[i], i);
        sort(names.begin(), names.end());
        for (int i = 0; i < (int)names.size(); i++) val[names[i].second] = {0, 0, -i};

        for (int i = 0; i < n; i++) FT[t].insert({0, 0, -i});
    }

    for (int i = 1; i <= 3 * n; i++)
        for (int j = i + 1; j <= 3 * n; j++) cmp[i][j].clear();

    auto insert = [&](int p) -> void { return FT[id[p]].insert(val[p]); };
    auto erase = [&](int p) -> void { return FT[id[p]].erase(val[p]); };
    auto genCmp = [&](int A, int B, int delt) -> void {
        if (cmp[A][B].empty()) return;
        auto [ver, vA, vB] = *cmp[A][B].begin();
        get<0>(val[A]) += delt * (vA > vB), get<0>(val[B]) += delt * (vB > vA);
        get<1>(val[A]) += delt * (vA - vB), get<1>(val[B]) += delt * (vB - vA);
        return;
    };

    int m = 0;
    while (q--) {
        int op = read();
        if (op == 1) {
            readString(), readString(), readString();
            string s = readString();
            s.pop_back();
            int A = rec[s];
            readString(), readString(), readString(), readString();
            readString(), readString(), readString();
            int B = rec[readString()];
            readString(), s = readString();
            int vA = s[0] - '0', vB = s[2] - '0';

            ccmp[++m] = {0, 0, 0, 0};
            if (id[A] != id[B] || A == B) continue;
            if (A > B) swap(A, B), swap(vA, vB);
            erase(A), erase(B);
            genCmp(A, B, -1);
            cmp[A][B].emplace(m, vA, vB), ccmp[m] = {A, B, vA, vB};
            genCmp(A, B, +1);
            insert(A), insert(B);
        } else if (op == 2) {
            int x = read();
            if (ccmp[x] == tiiii{0, 0, 0, 0}) continue;
            auto [A, B, vA, vB] = ccmp[x];
            erase(A), erase(B);
            genCmp(A, B, -1);
            cmp[A][B].erase({x, vA, vB}), ccmp[x] = {0, 0, 0, 0};
            genCmp(A, B, +1);
            insert(A), insert(B);
        } else {
            int x = read();
            cout << FT[id[x]].getRnk(val[x]) << endl;
        }
    }

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = read();
    while (_--) solve();

    return 0;
}