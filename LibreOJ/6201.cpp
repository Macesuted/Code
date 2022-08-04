/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
inline void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}
string getstr(void) {
    queue<char> que;
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) que.push(c), c = getch();
    string s;
    s.resize(que.size());
    for (register int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (register int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
inline T read() {
    register T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
inline void write(const T& t) {
    register T x = t;
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putch(qu[qr--]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 100005

typedef pair<int, int> pii;

struct Node {
    int tim, pos, pre, delta;
    inline bool operator<(const Node& oth) const { return this->pre < oth.pre; }
};
struct Ask {
    int id, tim, l, r;
    inline bool operator<(const Ask& oth) const { return this->l < oth.l; }
};

vector<Node> nodes;
vector<Ask> asks;

map<int, set<pii> > record;

int a[maxn], pre[maxn];

class ODT {
   private:
    map<pii, int> color;

    void split(int l, int mid, int r) {
        int col = color[(pii){l, mid}] = color[(pii){mid + 1, r}] = color[(pii){l, r}];
        color.erase((pii){l, r});
        record[col].erase((pii){l, r}), record[col].insert((pii){l, mid}), record[col].insert((pii){mid + 1, r});
        return;
    }
    void erase(int tim, int l, int r) {
        int col = color[(pii){l, r}];
        color.erase((pii){l, r});
        set<pii>::iterator i = ++record[col].find((pii){l, r});
        if (i != record[col].end())
            nodes.push_back((Node){tim, i->first, pre[i->first], -1}),
                nodes.push_back((Node){tim, i->first, pre[i->first] = pre[l], +1});
        nodes.push_back((Node){tim, l, pre[l], -1}), nodes.push_back((Node){tim, l, pre[l] = l - 1, +1});
        record[col].erase((pii){l, r});
        return;
    }

   public:
    inline void build(int l, int r, int col) {
        return color[(pii){l, r}] = col, record[col].insert((pii){l, r}), void();
    }
    void insert(int tim, int l, int r, int col) {
        map<pii, int>::iterator t = --color.lower_bound((pii){l + 1, 0});
        if (t->first.first != l) split(t->first.first, l - 1, t->first.second);
        t = --color.lower_bound((pii){r + 1, 0});
        if (t->first.second != r) split(t->first.first, r, t->first.second);
        while (true) {
            map<pii, int>::iterator i = color.lower_bound((pii){l, 0});
            if (i == color.end() || i->first.second > r) break;
            erase(tim, i->first.first, i->first.second);
        }
        record[col].insert((pii){l, r});
        set<pii>::iterator i = record[col].find((pii){l, r}), il = i, ir = i;
        int p = 0;
        if (il != record[col].begin()) p = (--il)->second;
        nodes.push_back((Node){tim, l, pre[l], -1}), nodes.push_back((Node){tim, l, pre[l] = p, +1});
        if (++ir != record[col].end())
            nodes.push_back((Node){tim, ir->first, pre[ir->first], -1}),
                nodes.push_back((Node){tim, ir->first, pre[ir->first] = r, +1});
        color[(pii){l, r}] = col;
        // t = color.find((pii){l, r});
        // if (t != color.begin() && (--t)->second == col) {
        //     int nl = t->first.first;
        //     record[col].erase((pii){t->first.first, t->first.second}), record[col].erase((pii){l, r});
        //     color.erase(t), color.erase((pii){l, r});
        //     record[col].insert((pii){l = nl, r});
        //     color[(pii){l, r}] = col;
        // }
        // t = ++color.find((pii){l, r});
        // if (t != color.end() && t->second == col) {
        //     int nr = t->first.second;
        //     record[col].erase((pii){t->first.first, t->first.second}), record[col].erase((pii){l, r});
        //     color.erase(t), color.erase((pii){l, r});
        //     record[col].insert((pii){l, r = nr});
        //     color[(pii){l, r}] = col;
        // }
        return;
    }
};
class BIT {
   private:
    int tree[maxn];

   public:
    void add(int p, int val) {
        for (register int i = p; i < maxn; i += i & -i) tree[i] += val;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (register int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
};

ODT tree;
BIT bit;

int answer[maxn];

void CDQ(int nl, int nr, int ql, int qr, int tl, int tr) {
    if (nl > nr || ql > qr) return;
    int tmid = (tl + tr) >> 1, nmid = nl - 1, qmid = ql - 1;
    while (nmid < nr && nodes[nmid + 1].tim <= tmid) nmid++;
    while (qmid < qr && asks[qmid + 1].tim <= tmid) qmid++;
    CDQ(nl, nmid, ql, qmid, tl, tmid), CDQ(nmid + 1, nr, qmid + 1, qr, tmid + 1, tr);
    if (nl > nmid || qmid + 1 > qr) return;
    sort(nodes.begin() + nl, nodes.begin() + nmid + 1), sort(asks.begin() + qmid + 1, asks.begin() + qr + 1);
    int j = nl;
    for (register int i = qmid + 1; i <= qr; i++) {
        while (j <= nmid && asks[i].l > nodes[j].pre) bit.add(nodes[j].pos, nodes[j].delta), j++;
        answer[asks[i].id] += bit.sum(asks[i].r) - bit.sum(asks[i].l - 1);
    }
    for (register int i = nl; i < j; i++) bit.add(nodes[i].pos, -nodes[i].delta);
    return;
}

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    for (register int i = 1, j; i <= n; i = j + 1) {
        j = i;
        while (j < n && a[j + 1] == a[i]) j++;
        tree.build(i, j, a[i]);
        set<pii>::iterator t = record[a[i]].find((pii){i, j});
        int p = 0;
        if (t != record[a[i]].begin()) p = (--t)->second;
        pre[i] = p;
        for (register int k = i + 1; k <= j; k++) pre[k] = k - 1;
    }
    for (register int i = 1; i <= n; i++) nodes.push_back((Node){0, i, pre[i], +1});
    for (register int i = 1; i <= m; i++)
        if (read<int>() == 1) {
            int l = read<int>(), r = read<int>(), col = read<int>();
            tree.insert(i, l, r, col);
        } else {
            int l = read<int>(), r = read<int>();
            asks.push_back((Ask){(int)asks.size(), i, l, r});
        }
    // for (vector<Node>::iterator i = nodes.begin(); i != nodes.end(); i++)
    //     cerr << i->tim << ' ' << i->pos << ' ' << i->pre << ' ' << i->delta << endl;
    CDQ(0, (int)nodes.size() - 1, 0, (int)asks.size() - 1, 0, m);
    for (register int i = 0; i < (int)asks.size(); i++) write(answer[i]), putch('\n');
    return 0;
}