/**
 * @file 1617E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}
string getstr(void) {
    string s = "";
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF) c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) s.push_back(c), c = getch();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
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

bool mem1;

typedef pair<int, int> pii;

struct Node {
    set<Node*> edges;
    int v;
    bool mark;
    Node(int _v) { v = _v, mark = false; }
};
Node* root = NULL;
map<int, Node*> rec;
map<int, int> rnk;

Node* getPointer(int v) { return rec.find(v) == rec.end() ? rec[v] = new Node(v) : rec[v]; }
int nex(int v) {
    int x = 1;
    while (x < v) x <<= 1;
    return x - v;
}
void insert(int v) {
    int f = nex(v);
    Node *fp = getPointer(f), *vp = getPointer(v);
    vp->mark = true;
    fp->edges.insert(vp), vp->edges.insert(fp);
    while (fp->edges.size() == 1 && f != 0)
        v = f, vp = fp, (fp = getPointer(f = nex(v)))->edges.insert(vp), vp->edges.insert(fp);
    if (root == NULL) root = fp;
    return;
}
pii dfs(Node* p, Node* pre = NULL) {
    pii ans = pii{p->mark ? -1 : -0x3f3f3f3f, p->v};
    for (auto i : p->edges)
        if (i != pre) ans = max(ans, dfs(i, p));
    return pii{ans.first + 1, ans.second};
}

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        insert(x), rnk[x] = i;
    }
    int a = dfs(root).second, b, d;
    tie(d, b) = dfs(rec[a]);
    cerr << a << ' ' << b << endl;
    write(rnk[a]), putch(' '), write(rnk[b]), putch(' '), write(d), putch('\n');
    return;
}

bool mem2;

int main() {
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
