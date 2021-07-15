/**
 * @author Macesuted (macesuted@qq.com)
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

#define maxlgn 60

long long a[maxlgn];
vector<long long> useful;
bool flag = false;

void insert(long long val) {
    for (register int i = maxlgn - 1; ~i && val; i--)
        if (val >> i & 1)
            if (a[i])
                val ^= a[i];
            else {
                for (register int j = i - 1; ~j; j--)
                    if (val >> j & 1) val ^= a[j];
                for (register int j = maxlgn - 1; j > i; j--)
                    if (a[j] >> i & 1) a[j] ^= val;
                return a[i] = val, void();
            }
    flag = true;
    return;
}

int main() {
    int n = read<int>();
    for (register int i = 1; i <= n; i++) insert(read<long long>());
    long long answer = 0;
    for (register int i = maxlgn - 1; ~i; i--)
        if (!(answer >> i & 1)) answer ^= a[i];
    for (register int i = 0; i < maxlgn; i++)
        if (a[i]) useful.push_back(a[i]);
    int m = useful.size();
    int q = read<int>();
    while (q--) {
        long long k = read<long long>() - flag;  // 如果所有数都是基那么不可能组出 0
        if ((1LL << m) <= k) {
            putstr("-1\n");
            continue;
        }
        long long answer = 0;
        for (register int i = 0; i < m; i++, k >>= 1)
            if (k & 1) answer ^= useful[i];
        write(answer), putch('\n');
    }
    return 0;
}