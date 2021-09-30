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
    for (int i = 0; i < (int)s.size(); i++) s[i] = que.front(), que.pop();
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
inline T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
inline void write(const T& t) {
    T x = t;
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

#define mod 1000000007
#define maxn 2005

int m, d;
long long f[2][maxn][maxn];

bool check(const string& s) {
    int pre = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (((i & 1) && s[i] != '0' + d) || (!(i & 1) && s[i] == '0' + d)) return false;
        pre = (pre * 10 + (s[i] - '0')) % m;
    }
    return pre == 0;
}
long long F(const string& s, bool i, int j, int k) {
    if (j >= (int)s.size()) return k == 0;
    if (f[i][j][k] >= 0) return f[i][j][k];
    long long answer = 0;
    for (int t = (j == 0); t <= (i ? s[j] - '0' : 9); t++)
        if (((j & 1) && t == d) || (!(j & 1) && t != d))
            answer = (answer + F(s, i & (s[j] - '0' == t), j + 1, (k * 10 + t) % m)) % mod;
    return f[i][j][k] = answer;
}
long long solve(const string& s) {
    memset(f, -1, sizeof(f));
    return F(s, true, 0, 0);
}

int main() {
    m = read<int>(), d = read<int>();
    string l = getstr(), r = getstr();
    write((solve(r) + mod - solve(l) + check(l)) % mod), putch('\n');
    return 0;
}