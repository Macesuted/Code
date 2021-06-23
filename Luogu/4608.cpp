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

#define maxn 3050

class BigInt {
#define base 1000000000
   public:
    vector<int> number;

    BigInt(void) { number.clear(); }

    inline BigInt& operator=(const int& b) { return number.clear(), number.push_back(b), *this; }
    BigInt operator+(const BigInt& b) const {
        BigInt a = *this;
        a.number.resize(max(a.number.size(), b.number.size()));
        for (register int i = 0; i < b.number.size(); i++) a.number[i] += b.number[i];
        for (register int i = 1; i < a.number.size(); i++)
            a.number[i] += a.number[i - 1] / base, a.number[i - 1] %= base;
        if (a.number.size() && a.number.back() >= base) {
            int rest = a.number.back() / base;
            a.number.back() %= base, a.number.push_back(rest);
        }
        return a;
    }

    void print(void) {
        if (number.empty()) return write(0);
        write(number.back());
        for (vector<int>::reverse_iterator i = number.rbegin() + 1; i != number.rend(); i++) {
            int t = *i;
            stack<int> S;
            for (register int j = 0; j < 9; j++) S.push(t % 10), t /= 10;
            while (!S.empty()) putch(S.top() + '0'), S.pop();
        }
        return;
    }
#undef base
};

string a, b;

BigInt f[maxn][maxn];
bool vis[maxn][maxn];
int pa[maxn][60], pb[maxn][60];
int answer = 0;

string str;

void dfs1(int p1, int p2) {
    putstr(str), putch('\n'), answer++;
    for (register int i = 0; i < 60; i++)
        if (pa[p1][i] && pb[p2][i]) {
            str.push_back('A' + i);
            dfs1(pa[p1][i], pb[p2][i]);
            str.pop_back();
        }
    return;
}
BigInt dfs2(int p1, int p2) {
    if (vis[p1][p2]) return f[p1][p2];
    vis[p1][p2] = true;
    f[p1][p2] = 1;
    for (register int i = 0; i < 60; i++)
        if (pa[p1][i] && pb[p2][i])
            f[p1][p2] = f[p1][p2] + dfs2(pa[p1][i], pb[p2][i]);
    return f[p1][p2];
}

int main() {
    int n = read<int>(), m = read<int>();
    a = ' ' + getstr(), b = ' ' + getstr();
    int k = read<int>();
    for (register int i = n; i; i--) {
        for (register int j = 0; j < 60; j++) pa[i][j] = pa[0][j];
        pa[0][a[i] - 'A'] = i;
    }
    for (register int i = m; i; i--) {
        for (register int j = 0; j < 60; j++) pb[i][j] = pb[0][j];
        pb[0][b[i] - 'A'] = i;
    }
    if (k == 1) {
        dfs1(0, 0);
        write(answer), putch('\n');
    } else {
        dfs2(0, 0).print();
        putch('\n');
    }
    return 0;
}