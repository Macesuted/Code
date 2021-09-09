/**
 * @author Macesuted (macesuted@outlook.com)
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

#define maxn 505

typedef pair<int, int> pii;

int a[maxn], b[maxn];
int f[maxn][maxn];

map<int, set<int> > record;

int Max(int& x, int y) { return x = (x > y ? x : y); }

int main() {
    int _ = read<int>();
    while (_--) {
        int n = read<int>();
        for (register int i = 1; i <= n; i++) a[i] = read<int>();
        int m = read<int>();
        for (register int i = 1; i <= m; i++) record[b[i] = read<int>()].insert(i);
        for (register int i = 1; i <= n; i++)
            for (register int j = 1; j <= m; j++)
                f[i][j] = 0;
        for (register int i = 1; i <= n; i++)
            if (record.find(a[i]) != record.end()) f[i][*record[a[i]].begin()] = 1;
        for (register int i = 1; i < n; i++)
            for (register int j = 1; j < m; j++)
                if (f[i][j])
                    for (register int k = i + 1; k <= n; k++)
                        if (a[k] > a[i] && record.find(a[k]) != record.end()) {
                            set<int>::iterator p = record[a[k]].upper_bound(j);
                            if (p == record[a[k]].end() || f[k][*p] >= f[i][j] + 1) continue;
                            f[k][*p] = f[i][j] + 1;
                        }
        int answer = 0;
        for (register int i = 1; i <= n; i++)
            for (register int j = 1; j <= m; j++)
                if (f[i][j] > answer) answer = f[i][j];
        write(answer), putch('\n');
        if (_) putch('\n');
        record.clear();
    }
    return 0;
}