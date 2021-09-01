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

#define maxn 105
#define maxt 20005

typedef pair<int, int> pii;

struct Range {
    int l, r, limit;
    inline bool operator<(const Range& oth) const { return this->limit < oth.limit; }
};

Range a[maxn];
bool v[maxt];
int speed[maxt];

int main() {
    int n = read<int>(), len = 0;
    for (register int i = 1; i <= n; i++) {
        int t = read<int>();
        a[i].l = len, a[i].r = len + t;
        len += t;
    }
    for (register int i = 1; i <= n; i++) a[i].limit = read<int>();
    sort(a + 1, a + n + 1);
    v[len] = true;
    double answer = 0;
    for (register int i = 1; i <= n; i++) {
        for (register int j = 0, pre = 0; j <= len; j++) {
            if (v[j] && pre < j) {
                int l = pre, r = j;
                if (speed[l] + (r - l) / 2. <= a[i].limit && ((r - l) & 1)) answer += 0.25;
                for (register int t = l + 1; t <= r - 1; t++)
                    speed[t] = min(a[i].limit, speed[l] + min(t - l, r - t));
                for (register int t = l; t < r; t++) v[t] = true;
                for (register int t = l; t < r; t++)
                    if (speed[t] == speed[t + 1] && speed[t] == a[i].limit) v[t] = false;
            }
            if (v[j]) pre = j + 1;
        }
        for (register int t = a[i].l; t < a[i].r; t++) v[t] = true;
    }
    for (register int i = 0; i < len; i++) answer += (speed[i] + speed[i + 1]) / 2.;
    cout << setprecision(11) << answer << endl;
    return 0;
}