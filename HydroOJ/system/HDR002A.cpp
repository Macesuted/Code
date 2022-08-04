/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My solution: https://macesuted.moe/article/hdr002a
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
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

#define maxn 1000005

typedef pair<int, int> pii;

pii pa[maxn], pb[maxn];
int amax[maxn], bmax[maxn];
int atail = 0, btail = 0;

int main() {
    int n = read<int>(), a = read<int>(), b = read<int>();
    for (register int i = 1; i <= n; i++) {
        int v = read<int>(), p = read<int>();
        char c = getstr()[0];
        (c == 'A' ? pa[++atail] : pb[++btail]) = (pii){p, v};
    }
    sort(pa + 1, pa + atail + 1), sort(pb + 1, pb + btail + 1);
    for (register int i = 1; i <= atail; i++) amax[i] = max(amax[i - 1], pa[i].second);
    for (register int i = 1; i <= btail; i++) bmax[i] = max(bmax[i - 1], pb[i].second);
    int answer = amax[upper_bound(pa + 1, pa + atail + 1, (pii){a + 1, 0}) - pa - 1] +
                 bmax[upper_bound(pb + 1, pb + btail + 1, (pii){b + 1, 0}) - pb - 1];
    for (register int i = 1, j = atail; i <= atail; i++) {
        if (a - pa[i].first < 0) continue;
        while (j >= 1 && pa[j].first > a - pa[i].first) j--;
        answer = max(answer, pa[i].second + amax[min(i - 1, j)]);
    }
    for (register int i = 1, j = btail; i <= btail; i++) {
        if (b - pb[i].first < 0) continue;
        while (j >= 1 && pb[j].first > b - pb[i].first) j--;
        answer = max(answer, pb[i].second + bmax[min(i - 1, j)]);
    }
    write(answer), putch('\n');
    return 0;
}