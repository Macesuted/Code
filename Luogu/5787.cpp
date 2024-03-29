/**
 * @author Macesuted (i@macesuted.moe)
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

typedef pair<int, int> pii;

vector<pii> tree[maxn << 2];

void insert(int p, int l, int r, int ql, int qr, pii val) {
    if (ql <= l && r <= qr) return tree[p].push_back(val);
    int mid = (l + r) >> 1;
    if (ql <= mid) insert(p << 1, l, mid, ql, qr, val);
    if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, val);
    return;
}

bool answer[maxn];
int fa[maxn << 1], sign[maxn << 1];

stack<pii> S;

int getfa(int p) { return fa[p] == p ? p : getfa(fa[p]); }
void merge(int x, int y) {
    if (sign[x] < sign[y]) swap(x, y);
    fa[y] = x, sign[x] += sign[x] == sign[y];
    S.push((pii){y, sign[x] == sign[y]});
    return;
}
void rollBack(void) {
    sign[fa[S.top().first]] -= S.top().second, fa[S.top().first] = S.top().first;
    return S.pop();
}

void dfs(int p, int l, int r) {
    for (vector<pii>::iterator i = tree[p].begin(); i != tree[p].end(); i++) {
        int gi = getfa(i->first), gj = getfa(i->second);
        if (gi == gj) {
            for (vector<pii>::iterator j = tree[p].begin(); j != i; j++) rollBack(), rollBack();
            return;
        }
        merge(gi, getfa(i->second + maxn)), merge(getfa(i->first + maxn), gj);
    }
    if (l == r) {
        for (vector<pii>::iterator j = tree[p].begin(); j != tree[p].end(); j++) rollBack(), rollBack();
        return answer[l] = true, void();
    }
    int mid = (l + r) >> 1;
    dfs(p << 1, l, mid), dfs(p << 1 | 1, mid + 1, r);
    for (vector<pii>::iterator j = tree[p].begin(); j != tree[p].end(); j++) rollBack(), rollBack();
    return;
}

int main() {
    int n = read<int>(), m = read<int>(), k = read<int>();
    for (register int i = 1; i <= m; i++) {
        pii t;
        t.first = read<int>(), t.second = read<int>();
        int from = read<int>(), to = read<int>();
        insert(1, 1, k, from + 1, to, t);
    }
    for (register int i = 1; i <= n; i++) fa[i] = i, fa[i + maxn] = i + maxn;
    dfs(1, 1, k);
    for (register int i = 1; i <= k; i++) putstr(answer[i] ? "Yes" : "No"), putch('\n');
    return 0;
}