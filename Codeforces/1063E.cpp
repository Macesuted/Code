/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief https://macesuted.moe/article/cf1063e/
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
inline void write(const T &t) {
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

#define maxn 1005

int a[maxn];
bool vis[maxn];
vector<int> mirror[maxn];
int tail = 1;
char out[maxn][maxn];

void work(int p) {
    int tp = a[p];
    while (tp != p) {
        if (tp < a[tp])
            mirror[tail].push_back(-tp), mirror[tail].push_back(-a[tp]);
        else
            mirror[tail].push_back(tp), mirror[tail].push_back(a[tp]);
        vis[tp] = true;
        tp = a[tp];
        tail++;
    }
    return;
}

int main() {
    int n = read<int>();
    bool check = true;
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    for (register int i = 1; i <= n; i++)
        if (i != a[i]) check = false;
    if (check) {
        write(n), putch('\n');
        for (register int i = 1; i <= n; i++) {
            for (register int j = 1; j <= n; j++) putch('.');
            putch('\n');
        }
        return 0;
    }
    write(n - 1), putch('\n');
    work(1);
    for (register int i = 2; i <= n; i++)
        if (!vis[i] && i != a[i]) {
            int rec = tail, p = i;
            while (a[p] > a[a[p]]) p = a[p];
            work(p);
            mirror[tail].push_back(1), mirror[tail].push_back(p);
            mirror[rec].push_back(-1);
            vis[p] = true;
            tail++;
        }
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= n; j++)
            out[i][j] = '.';
    for (register int i = 1; i <= n; i++)
        for (vector<int>::iterator j = mirror[i].begin(); j != mirror[i].end(); j++)
            out[i][abs(*j)] = *j < 0 ? '/' : '\\';
    for (register int i = 1; i <= n; i++) {
        for (register int j = 1; j <= n; j++) putch(out[i][j]);
        putch('\n');
    }
    return 0;
}