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

#define maxn 200005
#define maxS (1 << 15)

long long a[maxn];
int f[maxS], bitCnt[maxS];

int main() {
    int n = read<int>(), m = read<int>(), p = read<int>();
    for (register int i = 1; i <= n; i++)
        for (register int j = 0; j < m; j++) {
            char c = getch();
            while (c < '0' || c > '1') c = getch();
            a[i] |= (long long)(c ^ 48) << j;
        }
    srand(time(NULL));
    long long answer = 0, ansBit = 0;
    for (register int i = 1; i < maxS; i++) bitCnt[i] = bitCnt[i >> 1] + (i & 1);
    for (register int t = 80; t; t--) {
        int x = 1LL * rand() * rand() % n + 1;
        static vector<int> bitPos;
        bitPos.clear();
        for (register int i = 0; i < m; i++)
            if (a[x] >> i & 1) bitPos.push_back(i);
        memset(f, 0, sizeof(f));
        for (register int i = 1; i <= n; i++) {
            int S = 0;
            for (register int j = 0; j < (int)bitPos.size(); j++)
                if (a[i] >> bitPos[j] & 1) S |= 1 << j;
            f[S]++;
        }
        for (register int i = 0; i < (int)bitPos.size(); i++)
            for (register int j = 0; j < (1 << bitPos.size()); j++)
                if (!(j >> i & 1)) f[j] += f[j | (1 << i)];
        for (register int j = (1 << bitPos.size()) - 1; ~j; j--)
            if (f[j] * 2 >= n && ansBit < bitCnt[j]) {
                answer = 0, ansBit = bitCnt[j];
                for (register int i = 0; i < (int)bitPos.size(); i++)
                    if (j >> i & 1) answer |= 1LL << bitPos[i];
            }
    }
    for (register int i = 0; i < m; i++) write(answer >> i & 1);
    putch('\n');
    return 0;
}