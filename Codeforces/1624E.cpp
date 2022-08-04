/**
 * @file 1624E.cpp
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

#define maxn 1005

typedef tuple<int, int, int> tiii;

char a[maxn][maxn];
int fa[maxn];
tiii pre[maxn];

map<string, tiii> rec;

void solve(void) {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c = ' ';
            while (!('0' <= c && c <= '9')) c = getch();
            a[i][j] = c;
        }
    rec.clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++) {
            string s;
            s.push_back(a[i][j]), s.push_back(a[i][j + 1]);
            rec[s] = {j, j + 1, i};
            if (j + 1 < m) {
                s.push_back(a[i][j + 2]);
                rec[s] = {j, j + 2, i};
            }
        }
    string q = " " + getstr();
    fa[0] = 0;
    for (int i = 1; i <= m; i++) fa[i] = -1;
    for (int i = 1; i < m; i++) {
        if (!~fa[i - 1]) continue;
        string s;
        s.push_back(q[i]), s.push_back(q[i + 1]);
        if (rec.find(s) != rec.end() && !~fa[i + 1]) fa[i + 1] = i - 1, pre[i + 1] = rec[s];
        if (i + 1 < m) {
            s.push_back(q[i + 2]);
            if (rec.find(s) != rec.end() && !~fa[i + 2]) fa[i + 2] = i - 1, pre[i + 2] = rec[s];
        }
    }
    int p = m;
    while (p > 0) p = fa[p];
    if (!~p) return write(-1), putch('\n');
    stack<tiii> S;
    p = m;
    while (p > 0) S.push(pre[p]), p = fa[p];
    write((int)S.size()), putch('\n');
    while (!S.empty())
        write(get<0>(S.top())), putch(' '), write(get<1>(S.top())), putch(' '), write(get<2>(S.top())), putch('\n'),
            S.pop();
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
