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

#define maxd 505
#define maxs 5005

typedef pair<int, int> pii;

pii pre[maxd][maxs];
int use[maxd][maxs];

void dfs(int i, int j) {
    pii p = pre[i][j];
    if (p != (pii){-1, -1}) dfs(p.first, p.second);
    write(use[i][j]);
    return;
}
int main() {
    int d = read<int>(), s = read<int>();
    static queue<pii> que;
    for (register int i = 1; i <= 9; i++)
        if (i <= s) que.push({i % d, i}), pre[i % d][i] = {-1, -1}, use[i % d][i] = i;
    while (!que.empty()) {
        pii p = que.front();
        que.pop();
        if (p.first == 0 && p.second == s) break;
        for (register int i = 0; i <= 9; i++) {
            int x = (p.first * 10 + i) % d, y = p.second + i;
            if (y > s || pre[x][y] != (pii){0, 0}) continue;
            que.push({x, y}), pre[x][y] = p, use[x][y] = i;
        }
    }
    (pre[0][s] == (pii){0, 0}) ? write(-1) : dfs(0, s);
    putch('\n');
    return 0;
}