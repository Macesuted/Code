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

#define maxn 200005

int a[maxn], cnt[maxn], rec[maxn], pre[maxn], fir[maxn << 1];

vector<int> large;

void add(int p, int val) {
    rec[cnt[p]]--;
    cnt[p] += val;
    rec[cnt[p]]++;
    return;
}

int main() {
    int n = read<int>(), sqrtn = sqrt(n);
    for (register int i = 1; i <= n; i++) cnt[a[i] = read<int>()]++;
    int maxCnt = 0, tot = 0, maxPos;
    for (register int i = 1; i <= n; i++)
        if (cnt[i] > maxCnt)
            maxCnt = cnt[i], tot = 1, maxPos = i;
        else if (cnt[i] == maxCnt)
            tot++;
    if (tot > 1) return write(n), putch('\n'), 0;
    for (register int i = 1; i <= n; i++)
        if (cnt[i] > sqrtn && i != maxPos) large.push_back(i);
    int ans = 0;
    for (vector<int>::iterator i = large.begin(); i != large.end(); i++) {
        pre[0] = 0;
        for (register int j = 1; j <= n; j++) {
            pre[j] = pre[j - 1];
            if (a[j] == *i) pre[j]++;
            if (a[j] == maxPos) pre[j]--;
        }
        for (register int j = -n; j <= n; j++) fir[n + j] = n;
        fir[n + 0] = 0;
        for (register int j = 1; j <= n; j++) {
            fir[n + pre[j]] = min(fir[n + pre[j]], j);
            ans = max(ans, j - fir[n + pre[j]]);
        }
    }
    for (register int i = 1; i <= sqrtn; i++) {
        for (register int j = 1; j <= n; j++) cnt[j] = rec[j] = 0;
        for (register int l = 1, r = 1; r <= n; r++) {
            add(a[r], +1);
            while (cnt[a[r]] > i) add(a[l++], -1);
            if (rec[i] > 1) ans = max(ans, r - l + 1);
        }
    }
    write(ans), putch('\n');
    return 0;
}