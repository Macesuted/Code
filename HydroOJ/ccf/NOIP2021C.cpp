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
void putch(char x) {
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
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
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

#define maxn 10005
#define maxv 500005

bool mem1;

long long a[maxn], b[maxn], f[2][maxv];

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) a[i] = read<int>();
    for (int i = 1; i < n; i++) b[i] = a[i + 1] - a[i];
    sort(b + 1, b + n);
    int cnt = 0;
    for (int i = 1; i < n; i++)
        if (b[i] == 0) cnt++;
    for (int i = 1; i < n; i++) a[i] = a[i - 1] + b[i];
    memset(f[cnt & 1], 0x3f, sizeof(f[cnt & 1])), f[cnt & 1][0] = 0;
    for (int i = cnt + 1; i < n; i++) {
        bool thi = i & 1, tha = !thi;
        memset(f[thi], 0x3f, sizeof(f[thi]));
        for (int j = 0; j < maxv; j++) {
            if (f[tha][j] == 0x3f3f3f3f3f3f3f3f) continue;
            f[thi][j + a[i]] = min(f[thi][j + a[i]], f[tha][j] + a[i] * a[i]);
            f[thi][j + i * b[i]] = min(f[thi][j + i * b[i]], f[tha][j] + b[i] * b[i] * i + 2LL * b[i] * j);
        }
    }
    long long answer = numeric_limits<long long>::max();
    for (int i = 0; i < maxv; i++)
        if (f[(n - 1) & 1][i] != 0x3f3f3f3f3f3f3f3f)
            answer = min(answer, n * f[(n - 1) & 1][i] - 1LL * i * i);
    write(answer), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("variance.in", "r", stdin), freopen("variance.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
