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

#define maxn 1005

int a[maxn], cnt[10];
int answer = 1, n;
int f[maxn][1 << 8];

vector<int> pos[8];

bool check(int lim) {
    memset(cnt, 0, sizeof(cnt)), memset(f, -0x3f, sizeof(f));
    f[0][0] = 0;
    for (register int i = 0; i < n; i++) {
        for (register int j = 0; j < (1 << 8); j++)
            if (f[i][j] >= 0)
                for (register int k = 0; k < 8; k++)
                    if (!(j >> k & 1)) {
                        int p = cnt[k] + lim - 1;
                        if (p < pos[k].size()) f[pos[k][p]][j | (1 << k)] = max(f[pos[k][p]][j | (1 << k)], f[i][j]);
                        if (p + 1 < pos[k].size())
                            f[pos[k][p + 1]][j | (1 << k)] = max(f[pos[k][p + 1]][j | (1 << k)], f[i][j] + 1);
                    }
        if (i) cnt[a[i]]++;
    }
    int ans = -1;
    for (register int i = 0; i <= n; i++) ans = max(ans, f[i][(1 << 8) - 1]);
    if (ans == -1) return false;
    answer = max(answer, 8 * lim + ans);
    return true;
}

int main() {
    n = read<int>();
    for (register int i = 1; i <= n; i++) pos[a[i] = read<int>() - 1].push_back(i);
    int l = 1, r = n;
    for (register int i = 0; i < 8; i++) r = min(r, (int)pos[i].size());
    if (!r) {
        answer = 0;
        for (register int i = 0; i < 8; i++) answer += !pos[i].empty();
        write(answer), putch('\n');
        return 0;
    }
    while (l <= r) {
        int mid = (l + r) >> 1;
        check(mid) ? l = mid + 1 : r = mid - 1;
    }
    write(answer), putch('\n');
    return 0;
}