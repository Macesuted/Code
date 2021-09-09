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
    string s = "";
    char c = getch();
    while (c == ' ' || c == '\n' || c == '\r' || c == '\t') c = getch();
    while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t')) s.push_back(c), c = getch();
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

#define maxn 200005

typedef pair<int, int> pii;

map<int, int> rec[2];

int main() {
    int _ = read<int>();
    while (_--) {
        rec[0].clear(), rec[1].clear();
        int n = read<int>(), l = read<int>(), r = read<int>();
        for (register int i = 1; i <= l; i++) rec[0][read<int>()]++;
        for (register int i = 1; i <= r; i++) rec[1][read<int>()]++;
        int answer = 0;
        for (map<int, int>::iterator i = rec[0].begin(); i != rec[0].end(); i++) {
            map<int, int>::iterator j = rec[1].find(i->first);
            if (j == rec[1].end()) continue;
            int minVal = min(i->second, j->second);
            i->second -= minVal, j->second -= minVal;
            l -= minVal, r -= minVal;
        }
        map<int, int>*rec0 = &rec[0], *rec1 = &rec[1];
        if (l < r) swap(rec0, rec1), swap(l, r);
        for (map<int, int>::iterator i = rec0->begin(); i != rec0->end() && l > r; i++)
            while (l > r && i->second > 1) i->second -= 2, l -= 2, answer++;
        if (l > r) answer += (l - r) / 2;
        answer += (l + r) >> 1;
        write(answer), putch('\n');
    }
    return 0;
}