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

#define maxn 500005
#define maxsqrtn 1005

vector<int> record[maxn];
int a[maxn], b[maxn], lef[maxsqrtn], rig[maxsqrtn], f[maxsqrtn][maxsqrtn], cnt[maxn], bel[maxn], pos[maxn];

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) b[i] = a[i] = read<int>();
    sort(b + 1, b + n + 1);
    int tt = unique(b + 1, b + n + 1) - (b + 1);
    for (register int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + tt + 1, a[i]) - b,
                                          pos[i] = record[a[i]].size(), record[a[i]].push_back(i);
    int block = sqrt(n);
    int length = block ? n / block : n;
    for (register int i = 1; i <= block; i++) lef[i] = rig[i - 1] + 1, rig[i] = rig[i - 1] + length;
    if (rig[block] < n) lef[block + 1] = rig[block] + 1, rig[++block] = n;
    for (register int i = 1; i <= block; i++)
        for (register int j = lef[i]; j <= rig[i]; j++)
            bel[j] = i;
    for (register int i = 1; i <= block; i++) {
        for (register int j = lef[i]; j <= n; j++) f[i][bel[j]] = max(f[i][bel[j]], max(f[i][bel[j] - 1], ++cnt[a[j]]));
        for (register int j = lef[i]; j <= n; j++) cnt[a[j]]--;
    }
    int lastans = 0;
    while (m--) {
        int l = read<int>() ^ lastans, r = read<int>() ^ lastans;
        int L = bel[l], R = bel[r];
        int answer = 0;
        if (L == R) {
            for (register int i = l; i <= r; i++) answer = max(answer, ++cnt[a[i]]);
            for (register int i = l; i <= r; i++) cnt[a[i]]--;
        } else {
            answer = f[L + 1][R - 1];
            for (register int i = l; i <= rig[L]; i++)
                while (pos[i] + answer < record[a[i]].size() && record[a[i]][pos[i] + answer] <= r) answer++;
            for (register int i = lef[R]; i <= r; i++)
                while (pos[i] - answer >= 0 && record[a[i]][pos[i] - answer] >= l) answer++;
        }
        write(lastans = answer), putch('\n');
    }
    return 0;
}