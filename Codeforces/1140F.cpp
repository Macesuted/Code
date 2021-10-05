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

#define maxn 300005

typedef pair<int, int> pii;

vector<pii> tree[maxn << 2];

void insert(int p, int l, int r, int ql, int qr, pii val) {
    if (ql <= l && r <= qr) return tree[p].push_back(val);
    int mid = (l + r) >> 1;
    if (ql <= mid) insert(p << 1, l, mid, ql, qr, val);
    if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, val);
    return;
}

map<long long, int> record;

long long answer[maxn], siz[2][maxn << 1], sum = 0;
int fa[maxn << 1];

stack<pii> S;

int getfa(int p) { return fa[p] == p ? p : getfa(fa[p]); }
void merge(int x, int y) {
    x = getfa(x), y = getfa(y);
    if (siz[0][x] + siz[1][x] < siz[0][y] + siz[1][y]) swap(x, y);
    S.push((pii){x, y});
    if (x == y) return;
    fa[y] = x;
    sum -= siz[0][x] * siz[1][x] + siz[0][y] * siz[1][y];
    siz[0][x] += siz[0][y], siz[1][x] += siz[1][y];
    sum += siz[0][x] * siz[1][x];
    return;
}
void rollBack(void) {
    int x = S.top().first, y = S.top().second;
    S.pop();
    if (x == y) return;
    sum -= siz[0][x] * siz[1][x];
    siz[0][x] -= siz[0][y], siz[1][x] -= siz[1][y];
    sum += siz[0][x] * siz[1][x] + siz[0][y] * siz[1][y];
    fa[y] = y;
    return;
}

void dfs(int p, int l, int r) {
    for (vector<pii>::iterator i = tree[p].begin(); i != tree[p].end(); i++) merge(i->first, i->second + maxn);
    if (l == r) {
        answer[l] = sum;
        for (vector<pii>::iterator i = tree[p].begin(); i != tree[p].end(); i++) rollBack();
        return;
    }
    int mid = (l + r) >> 1;
    dfs(p << 1, l, mid), dfs(p << 1 | 1, mid + 1, r);
    for (vector<pii>::iterator i = tree[p].begin(); i != tree[p].end(); i++) rollBack();
    return;
}

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) {
        pii t;
        t.first = read<int>(), t.second = read<int>();
        long long val = 1LL * t.first * maxn + t.second;
        map<long long, int>::iterator j = record.find(val);
        if (j == record.end())
            record[val] = i;
        else
            insert(1, 1, n, j->second, i - 1, t), record.erase(j);
    }
    for (map<long long, int>::iterator i = record.begin(); i != record.end(); i++)
        insert(1, 1, n, i->second, n, (pii){i->first / maxn, i->first % maxn});
    record.clear();
    for (register int i = 1; i < maxn; i++) fa[i] = i, siz[0][i] = 1, fa[i + maxn] = i + maxn, siz[1][i + maxn] = 1;
    dfs(1, 1, n);
    for (register int i = 1; i <= n; i++) write(answer[i]), putch(" \n"[i == n]);
    return 0;
}