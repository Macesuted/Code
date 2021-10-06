/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <cstdio>
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iomanip>
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
    for (int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
inline T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
inline void write(const T& t) {
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

typedef pair<int, int> pii;

pii getPos(int n, int p) {
    if (n == 0) return {1, 1};
    int L = 1 << (n - 1), S = L * L;
    if (p <= S) {
        pii ret = getPos(n - 1, S - p + 1);
        return {ret.second, L - ret.first + 1};
    }
    if (p <= 2 * S) {
        pii ret = getPos(n - 1, p - S);
        return {ret.first, ret.second + L};
    }
    if (p <= 3 * S) {
        pii ret = getPos(n - 1, p - 2 * S);
        return {ret.first + L, ret.second + L};
    }
    pii ret = getPos(n - 1, 4 * S - p + 1);
    return {2 * L - ret.second + 1, ret.first};
}

inline double dist(pii a, pii b) {
    return 10 * sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

int main() {
    ios::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(0);
    int _ = read<int>();
    while (_--) {
        int n = read<int>(), x = read<int>(), y = read<int>();
        pii xpos = getPos(n, x), ypos = getPos(n, y);
        cout << dist(xpos, ypos) << endl;
    }
    return 0;
}