/**
 * @file 453E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-20
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      My Tutorial: https://macesuted.moe/article/cf453e
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::getch;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

#define maxn 100005

typedef pair<long long, long long> pll;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        long long sumR, sumM;
        Node(void) { l = r = NULL, sumR = sumM = 0; }
    };

    vector<Node*> roots;
    int n;

    Node* newRoot(void) { return roots.push_back(roots.back()), roots.back(); }
    void exist(Node*& p, Node* o) {
        if (p != o && p != NULL) return;
        return p = new Node(), *p = *o, void();
    }
    void pushUp(Node* p) {
        p->sumR = p->sumM = 0;
        if (p->l != NULL) p->sumR += p->l->sumR, p->sumM += p->l->sumM;
        if (p->r != NULL) p->sumR += p->r->sumR, p->sumM += p->r->sumM;
        return;
    }
    pll merge(pll a, pll b) { return {a.first + b.first, a.second + b.second}; }
    void insert(Node*& p, Node* o, int l, int r, int qp, int vr, int vm) {
        if (o == NULL) p = o = new Node();
        exist(p, o);
        if (l == r) return p->sumR = vr, p->sumM = vm, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, o->l, l, mid, qp, vr, vm) : insert(p->r, o->r, mid + 1, r, qp, vr, vm);
        return pushUp(p);
    }
    pll query(Node* p, int l, int r, int ql, int qr) {
        if (p == NULL) return {0, 0};
        if (ql <= l && r <= qr) return {p->sumR, p->sumM};
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
        return merge(query(p->l, l, mid, ql, qr), query(p->r, mid + 1, r, ql, qr));
    }

   public:
    SegmentTree(void) { roots.push_back(NULL); }
    void resize(int _n) { return n = _n, void(); }
    void insert(int p, int r, int m) {
        return newRoot(), insert(roots.back(), roots[(int)roots.size() - 2], 1, n, p, r, m);
    }
    pll query(int ver, int l, int r) { return query(roots[ver], 1, n, l, r); }
} ST;

pair<double, int> t[maxn];
long long rsum[maxn];

class OldDriverTree {
   private:
    struct Node {
        int l, r;
        double tim;
        bool operator<(const Node& oth) const { return this->l < oth.l; }
    };

    set<Node> S;
    int n;

    void split(Node p, int v) {
        S.erase(p), S.insert({p.l, v, p.tim});
        if (v < p.r) S.insert({v + 1, p.r, p.tim});
        return;
    }

   public:
    void build(int _n, double b[]) {
        n = _n;
        for (int l = 1, r; l <= n; l = r + 1) {
            r = l;
            while (r < n && b[r + 1] == b[r]) r++;
            S.insert({l, r, b[l]});
        }
        return;
    }
    long long query(int T, int l, int r) {
        auto x = --S.lower_bound({l + 1, 0, 0});
        if (x->l != l) split(*x, l - 1);
        x = --S.lower_bound({r + 1, 0, 0});
        if (x->r != r) split(*x, r);
        long long ans = 0;
        for (auto i = S.lower_bound({l, 0, 0}); i != S.end() && i->r <= r; i = S.erase(i)) {
            double tim = T - i->tim;
            int p = lower_bound(t + 1, t + n + 1, make_pair(tim, 0)) - t;
            pll ret = ST.query(p - 1, i->l, i->r);
            ans += ret.second + (long long)((rsum[i->r] - rsum[i->l - 1] - ret.first) * tim + 0.5);
        }
        S.insert({l, r, (double)T});
        return ans;
    }
} ODT;

int s[maxn], m[maxn], r[maxn];
double b[maxn];

set<pll> S;

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        s[i] = read<int>(), m[i] = read<int>(), r[i] = read<int>();
        if (r[i])
            t[i] = {1. * m[i] / r[i], i}, b[i] = -1. * s[i] / r[i];
        else
            S.emplace(i, s[i]), t[i] = {1e18, i}, b[i] = 0;
    }
    for (int i = 1; i <= n; i++) rsum[i] = rsum[i - 1] + r[i];
    sort(t + 1, t + n + 1);
    ST.resize(n), ODT.build(n, b);
    for (int i = 1; i <= n; i++) ST.insert(t[i].second, r[t[i].second], m[t[i].second]);
    int q = read<int>();
    while (q--) {
        int t = read<int>(), l = read<int>(), r = read<int>();
        long long ans = ODT.query(t, l, r);
        for (auto i = S.lower_bound({l, 0}); i != S.end() && i->first <= r; i = S.erase(i)) ans += i->second;
        write(ans), putch('\n');
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
