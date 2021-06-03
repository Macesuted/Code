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
inline void write(const T &t) {
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

#define int long long
#define mod 998244353
// 1000000007

typedef pair<int, int> pii;

int power(int a, int x) {
    int answer = 1;
    while (x) {
        if (x & 1) answer = answer * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return answer;
}

struct str {
    int pl, pr;
    int vl, vr;
};

vector<vector<int> > graph;

int a[100005];

vector<str> answer;

signed main() {
    ios::sync_with_stdio(false);
    int _ = 1;
    _ = read<int>();
    while (_--) {
        int n = read<int>();
        a[0] = 1e9 + 1;
        int minPos = 0;
        for (register int i = 1; i <= n; i++) {
            a[i] = read<int>();
            if (a[i] < a[minPos]) minPos = i;
        }
        if (minPos != 1) answer.push_back((str){1, minPos, a[minPos], a[1]});
        long long e9 = 1e9;
        if (n > 1) answer.push_back((str){1, 2, a[minPos], e9 + 7});
        for (register int i = 3; i <= n; i++) answer.push_back((str){1, i, a[minPos], e9 + i + 5});
        write((int)answer.size()), putch('\n');
        for (vector<str>::iterator i = answer.begin(); i != answer.end(); i++)
            write(i->pl), putch(' '), write(i->pr), putch(' '), write(i->vl), putch(' '), write(i->vr), putch('\n');
        answer.clear();
    }
    return 0;
} // awa