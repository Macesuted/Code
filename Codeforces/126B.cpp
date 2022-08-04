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

template <long long base, long long mod>
class Hash {
   public:
    int n;
    int a[maxn];
    vector<long long> pow, f;
    void build(void) {
        pow.resize(n + 1), f.resize(n + 1);
        pow[0] = 1;
        for (register int i = 1; i <= n; i++) {
            pow[i] = pow[i - 1] * base % mod;
            f[i] = (f[i - 1] * base + a[i]) % mod;
        }
        return;
    }
    long long get(int l, int r) { return (f[r] + mod - f[l - 1] * pow[r - l + 1] % mod) % mod; }
};

string str;

int a[maxn];
Hash<31, 1000000007> hash1;
Hash<31, 1000000007> hash2;

bool same(int l1, int r1, int l2, int r2) {
    return hash1.get(l1, r1) == hash1.get(l2, r2) && hash2.get(l1, r1) == hash2.get(l2, r2);
}

int main() {
    str = ' ' + getstr();
    int n = str.size() - 1;
    for (register int i = 1; i <= n; i++) a[i] = str[i] - 'a';
    hash1.n = hash2.n = n;
    for (register int i = 1; i <= n; i++) hash1.a[i] = hash2.a[i] = a[i];
    hash1.build(), hash2.build();
    int ansl = -1, ansr = -1;
    for (register int i = 1, l = 2; i < n; i++) {
        if (!same(1, i, n - i + 1, n)) continue;
        while (l + i - 1 < n && !same(1, i, l, l + i - 1)) l++;
        if (l + i - 1 >= n) break;
        ansl = l, ansr = l + i - 1;
    }
    if (ansl == -1)
        putstr("Just a legend");
    else
        for (register int i = ansl; i <= ansr; i++) putch('a' + a[i]);
    putch('\n');
    return 0;
}