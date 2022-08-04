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
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
inline void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
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
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 200005

int u[maxn];
vector<vector<int> > rec;
vector<long long> pre;
long long answer[maxn];

int main() {
    int _ = read<int>();
    while (_--) {
        int n = read<int>();
        rec.resize(n + 1);
        memset(answer, 0, sizeof(answer));
        for (register int i = 1; i <= n; i++) u[i] = read<int>();
        for (register int i = 1; i <= n; i++) rec[u[i]].push_back(read<int>());
        for (register int i = 1; i <= n; i++)
            if (rec[i].size()) {
                sort(rec[i].begin(), rec[i].end(), greater<int>());
                pre.push_back(0);
                for (vector<int>::iterator j = rec[i].begin(); j != rec[i].end(); j++) pre.push_back(pre.back() + *j);
                for (register int j = 1; j <= rec[i].size(); j++) answer[j] += pre[rec[i].size() / j * j];
                pre.clear();
            }
        for (register int i = 1; i <= n; i++) write(answer[i]), putch(" \n"[i == n]);
        rec.clear();
    }
    return 0;
}