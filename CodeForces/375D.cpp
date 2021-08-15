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
inline char getch(void) { return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++); }
inline void putch(char x) {
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

int a[maxn], dfni[maxn], dfno[maxn], v[maxn], cnt[maxn], rec[maxn];

struct Ask {
    int id, l, r, lim, bel;
    inline bool operator<(const Ask& oth) const {
        return this->bel != oth.bel ? this->l < oth.l : ((this->bel & 1) ? this->r > oth.r : this->r < oth.r);
    }
};

Ask ask[maxn];

int answer[maxn];

vector<vector<int> > graph;

int tim = 0;
void dfs(int p, int pre = -1) {
    dfni[p] = ++tim;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) dfs(*i, p);
    dfno[p] = tim;
    return;
}

int tree[maxn];
void add(int p, int val) {
    for (register int i = p; i < maxn; i += i & -i) tree[i] += val;
    return;
}
int sum(int p) {
    int sum = 0;
    for (register int i = p; i; i -= i & -i) sum += tree[i];
    return sum;
}

void add(int p) {
    if (cnt[v[p]]) add(cnt[v[p]], -1);
    cnt[v[p]]++;
    add(cnt[v[p]], 1);
    return;
}
void del(int p) {
    add(cnt[v[p]], -1);
    cnt[v[p]]--;
    if (cnt[v[p]]) add(cnt[v[p]], 1);
    return;
}

int main() {
    int n = read<int>(), m = read<int>(), sqrtn = sqrt(n);
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int from = read<int>(), to = read<int>();
        graph[from].push_back(to), graph[to].push_back(from);
    }
    dfs(1);
    for (register int i = 1; i <= n; i++) v[dfni[i]] = a[i];
    for (register int i = 1, p; i <= m; i++) {
        p = read<int>(), ask[i].lim = read<int>();
        ask[i].l = dfni[p], ask[i].r = dfno[p], ask[i].id = i, ask[i].bel = ask[i].l / sqrtn;
    }
    sort(ask + 1, ask + m + 1);
    for (register int i = 1, l = 1, r = 0; i <= m; i++) {
        while (l > ask[i].l) add(--l);
        while (r < ask[i].r) add(++r);
        while (l < ask[i].l) del(l++);
        while (r > ask[i].r) del(r--);
        answer[ask[i].id] = sum(maxn - 1) - sum(ask[i].lim - 1);
    }
    for (register int i = 1; i <= m; i++) write(answer[i]), putch('\n');
    return 0;
}