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

#define mod 998244353
#define maxn 1000005

long long power(long long a, long long x) {
    long long answer = 1;
    while (x) {
        if (x & 1) answer = answer * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return answer;
}

int a[maxn], pos[maxn];

int main() {
    int _ = read<int>();
    while (_--) {
        int n = read<int>(), cnt = 0;
        long long answer = 0x3f3f3f3f3f3f3f3f, tot = 0;
        for (register int i = 1; i <= n; i++) {
            char c = getch();
            while (c != '*' && c != '.') c = getch();
            a[i] = (c == '*');
            if (a[i]) cnt++, tot += i - cnt, pos[cnt] = i - cnt;
        }
        answer = tot;
        for (register int delta = 1, j = 0; delta + cnt <= n; delta++) {
            while (j < cnt && pos[j + 1] < delta) j++;
            tot -= cnt - j, tot += j;
            answer = min(answer, tot);
        }
        write(answer), putch('\n');
    }
    return 0;
}//awa