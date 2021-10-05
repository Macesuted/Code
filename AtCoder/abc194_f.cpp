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
#define mod 1000000007

string str;
int a[maxn];
bool vis[17];
int cnt = 0;
long long f[maxn][17];

int main() {
    str = " " + getstr();
    int n = str.size() - 1;
    for (register int i = 1; i <= n; i++)
        if ('0' <= str[i] && str[i] <= '9')
            a[i] = str[i] - '0';
        else
            a[i] = str[i] - 'A' + 10;
    int k = read<int>();
    vis[a[1]] = true, cnt = 1, f[1][1] = a[1] - 1;
    for (register int i = 2; i <= n; i++) {
        f[i][1] = (f[i - 1][1] + 15) % mod;
        for (register int j = 2; j <= k; j++)
            f[i][j] = (f[i][j] + f[i - 1][j - 1] * (16 - j + 1) + f[i - 1][j] * j) % mod;
        for (register int t = 0; t < a[i]; t++) f[i][cnt + (!vis[t])]++;
        if (!vis[a[i]]) cnt++;
        vis[a[i]] = true;
    }
    long long answer = f[n][k];
    if (cnt == k) answer = (answer + 1) % mod;
    write(answer), putch('\n');
    return 0;
}