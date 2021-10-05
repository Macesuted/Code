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

#define maxn 1000005

string s;

int p[maxn], fa[maxn];

int getfa(int k) { return fa[k] == k ? k : fa[k] = getfa(fa[k]); }

int main() {
    ios::sync_with_stdio(false);
    int _;
    cin >> _;
    while (_--) {
        cin >> s;
        s = '$' + s + '#';
        int n = s.size() - 1;
        for (register int i = 1, mid = 0, r = 0; i <= n; i++) {
            p[i] = 0;
            if (i <= r) p[i] = min(r - i + 1, p[mid * 2 - i]);
            while (s[i - p[i]] == s[i + p[i]]) p[i]++;
            if (i + p[i] > r) r = (mid = i) + p[i] - 1;
            p[i]--;
        }
        n--;
        for (register int i = 0; i <= n; i++) fa[i] = i;
        for (register int i = 1; i <= n; i++) {
            if (i - p[i] == 1) fa[getfa(i)] = getfa(i + p[i]);
            if (i + p[i] == n) fa[getfa(i)] = 0;
        }
        for (register int i = 1; i <= n; i++)
            if (getfa(i) == 0) write(i), putch(' ');
        putch('\n');
    }
    return 0;
}