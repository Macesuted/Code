/**
 * @file 1623E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-08
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

#define maxn 200005

typedef pair<int, int> pii;

string c, S;
int pos[maxn];
bool good[maxn], mark[maxn];
pii son[maxn];
stack<int> sta;

void dfs1(int p) {
    if (son[p].first) dfs1(son[p].first);
    pos[S.size()] = p, S.push_back(c[p]);
    if (son[p].second) dfs1(son[p].second);
    return;
}
int dfs2(int p, int rest) {
    if (rest <= (int)sta.size()) return rest;
    sta.push(p);
    int cost = 0;
    if (son[p].first && (cost = dfs2(son[p].first, rest)) < rest) rest = cost - 1, mark[p] = true, sta.pop();
    if (!mark[p] && good[p]) rest--, mark[p] = true, sta.pop();
    if (son[p].second && mark[p]) rest = dfs2(son[p].second, rest);
    if (!mark[p]) sta.pop();
    return rest;
}
void dfs3(int p) {
    if (son[p].first) dfs3(son[p].first);
    putch(c[p]);
    if (mark[p]) putch(c[p]);
    if (son[p].second) dfs3(son[p].second);
    return;
}

void solve(void) {
    int n = read<int>(), k = read<int>();
    c = " " + getstr();
    for (int i = 1; i <= n; i++) son[i].first = read<int>(), son[i].second = read<int>();
    S = " ";
    dfs1(1);
    char last = ' ';
    for (int i = n; i; i--) {
        if (i < n && S[i] != S[i + 1]) last = S[i + 1];
        if (S[i] < last) good[pos[i]] = true;
    }
    dfs2(1, k);
    dfs3(1);
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
