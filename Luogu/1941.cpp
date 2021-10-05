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

#define maxn 10005
#define maxm 1005

typedef pair<int, int> pii;

int f[maxn][maxm];
int up[maxn], down[maxn];
pii lim[maxn];

int main() {
    //    freopen("bird.in", "r", stdin), freopen("bird.out", "w", stdout);
    int n = read<int>(), m = read<int>(), k = read<int>();
    for (register int i = 1; i <= n; i++) up[i] = read<int>(), down[i] = read<int>();
    for (register int i = 1; i <= k; i++) {
        int p = read<int>(), l = read<int>(), r = read<int>();
        lim[p] = (pii){l, r};
    }
    memset(f, 0x3f, sizeof(f));
    for (register int i = 1; i <= m; i++) f[0][i] = 0;
    for (register int i = 1, cnt = 0; i <= n; i++) {
        int l = 1, r = m;
        if (lim[i] != (pii){0, 0}) l = lim[i].first + 1, r = lim[i].second - 1;
        for (register int j = 1; j <= m; j++) {
            int to = min(j + up[i], m);
            f[i][to] = min(f[i][to], min(f[i][j], f[i - 1][j]) + 1);
        }
        for (register int j = 1; j < l; j++) f[i][j] = 0x3f3f3f3f;
        for (register int j = r + 1; j <= m; j++) f[i][j] = 0x3f3f3f3f;
        for (register int j = down[i] + 1; j <= m; j++) {
            int to = j - down[i];
            if (!(l <= to && to <= r)) continue;
            f[i][to] = min(f[i][to], f[i - 1][j]);
        }
        bool check = true;
        for (register int j = 1; j <= m; j++)
            if (f[i][j] != 0x3f3f3f3f) check = false;
        if (check) return write(0), putch('\n'), write(cnt), putch('\n'), 0;
        if (lim[i] != (pii){0, 0}) cnt++;
    }
    int answer = 0x3f3f3f3f;
    for (register int j = 1; j <= m; j++) answer = min(answer, f[n][j]);
    write(1), putch('\n'), write(answer), putch('\n');
    return 0;
}
