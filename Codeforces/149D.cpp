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

#define maxn 705
#define mod 1000000007

long long f[maxn][maxn][3][3];

string s;

stack<int> S;
int match[maxn];

long long sum(int l, int r) {
    long long sum = 0;
    for (register int i = 0; i < 3; i++)
        for (register int j = 0; j < 3; j++)
            sum += f[l][r][i][j];
    return sum % mod;
}
void dfs(int l, int r) {
    if (l + 1 == r) {
        f[l][r][0][1] = f[l][r][0][2] = f[l][r][1][0] = f[l][r][2][0] = 1;
        return;
    }
    int p = match[l];
    if (p == r) {
        dfs(l + 1, r - 1);
        int tot = sum(l + 1, r - 1);
        f[l][r][0][1] = (tot - f[l + 1][r - 1][0][1] - f[l + 1][r - 1][1][1] - f[l + 1][r - 1][2][1] + 3LL * mod) % mod;
        f[l][r][0][2] = (tot - f[l + 1][r - 1][0][2] - f[l + 1][r - 1][1][2] - f[l + 1][r - 1][2][2] + 3LL * mod) % mod;
        f[l][r][1][0] = (tot - f[l + 1][r - 1][1][0] - f[l + 1][r - 1][1][1] - f[l + 1][r - 1][1][2] + 3LL * mod) % mod;
        f[l][r][2][0] = (tot - f[l + 1][r - 1][2][0] - f[l + 1][r - 1][2][1] - f[l + 1][r - 1][2][2] + 3LL * mod) % mod;
        return;
    }
    dfs(l, p), dfs(p + 1, r);
    for (register int a = 0; a < 3; a++)
        for (register int b = 0; b < 3; b++)
            for (register int x = 0; x < 3; x++)
                for (register int y = 0; y < 3; y++)
                    if (x != y || x == 0)
                        f[l][r][a][b] = (f[l][r][a][b] + f[l][p][a][x] * f[p + 1][r][y][b]) % mod;
    return;
}

int main() {
    s = ' ' + getstr();
    int n = s.size() - 1;
    for (register int i = 1; i <= n; i++) (s[i] == '(') ? S.push(i) : (match[S.top()] = i, S.pop());
    dfs(1, n);
    write(sum(1, n)), putch('\n');
    return 0;
}