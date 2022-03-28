/**
 * @file 4369.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-28
 *
 * @copyright Copyright (c) 2022
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

#define maxn 500005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

class SegmentTree {
   private:
    struct Node {
        Node *l, *r;
        int sum;
        Node(void) { l = r = NULL, sum = 0; }
    };

    vector<Node*> roots;
    int n;

    void pushUp(Node* p) {
        p->sum = 0;
        if (p->l != NULL) p->sum += p->l->sum;
        if (p->r != NULL) p->sum += p->r->sum;
        return;
    }
    void insert(Node*& p, Node* o, int l, int r, int qp) {
        if (p == o) {
            p = new Node();
            if (o != NULL) *p = *o;
        }
        if (l == r) return p->sum++, void();
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, o == NULL ? NULL : o->l, l, mid, qp) : insert(p->r, o == NULL ? NULL : o->r, mid + 1, r, qp);
        return pushUp(p);
    }
    int query(Node* p, int l, int r, int ql, int qr) {
        if (p == NULL) return 0;
        if (ql <= l && r <= qr) return p->sum;
        int mid = (l + r) >> 1;
        if (qr <= mid) return query(p->l, l, mid, ql, qr);
        if (ql > mid) return query(p->r, mid + 1, r, ql, qr);
        return query(p->l, l, mid, ql, qr) + query(p->r, mid + 1, r, ql, qr);
    }
    int findKTh(Node* p1, Node* p2, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1,
            pv = (p2 == NULL || p2->l == NULL ? 0 : p2->l->sum) - (p1 == NULL || p1->l == NULL ? 0 : p1->l->sum);
        if (pv < k) return findKTh(p1 == NULL ? NULL : p1->r, p2 == NULL ? NULL : p2->r, mid + 1, r, k - pv);
        return findKTh(p1 == NULL ? NULL : p1->l, p2 == NULL ? NULL : p2->l, l, mid, k);
    }

   public:
    SegmentTree(void) { roots.push_back(NULL); }
    void resize(int _n) { return n = _n, void(); }
    void newVer(void) { return roots.push_back(roots.back()); }
    void insert(int p) { return insert(roots.back(), *++roots.rbegin(), 1, n, p); }
    int query(int vl, int vr, int l, int r) { return query(roots[vr], 1, n, l, r) - query(roots[vl - 1], 1, n, l, r); }
    int findKTh(int vl, int vr, int k) { return findKTh(roots[vl - 1], roots[vr], 1, n, k); }
} ST;

pii a[maxn];
int ques[maxn];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i].first = read<int>(), a[i].second = read<int>();
    sort(a + 1, a + n + 1);
    ST.resize(n);
    for (int i = 1, j = 1; i <= n; i++) {
        ST.newVer();
        while (j <= n && a[j].first <= i) ST.insert(a[j++].second);
    }
    int q = read<int>();
    while (q--) {
        int m = read<int>();
        for (int i = 1; i <= m; i++) ques[i] = read<int>();
        sort(ques + 1, ques + m + 1);
        static stack<tiii> S;
        while (!S.empty()) S.pop();
        S.emplace(0, n + 1, 0);
        bool check = true;
        for (int i = 1; i <= m; i++) {
            int rest = ques[i], h = ques[i], t;
            while (get<1>(S.top()) < ques[i]) S.pop();
            if (get<1>(S.top()) == ques[i]) rest += get<2>(S.top()), S.pop();
            while (!S.empty() && (t = ST.query(get<0>(S.top()) + 1, ques[i], h, get<1>(S.top()) - 1)) <= rest)
                h = get<1>(S.top()), rest -= t - get<2>(S.top()), S.pop();
            if (S.empty() && rest) {
                check = false;
                break;
            }
            if (rest) {
                int p = ST.findKTh(get<0>(S.top()) + 1, ques[i], ST.query(get<0>(S.top()) + 1, ques[i], 1, h - 1) + rest);
                rest -= ST.query(get<0>(S.top()) + 1, ques[i], h, p - 1), h = p;
                if (rest == ST.query(get<0>(S.top()) + 1, ques[i], p, p)) rest = 0, h = p + 1;
            }
            S.emplace(ques[i], h, rest);
        }
        write((int)check), putch('\n');
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
