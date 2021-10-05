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

#define maxv 20000005

vector<int> prime;
bool notPrime[maxv];

void init(void) {
    notPrime[1] = true;
    for (register int i = 2; i < maxv; i++) {
        if (!notPrime[i]) prime.push_back(i);
        for (vector<int>::iterator j = prime.begin(); i * *j < maxv; j++) {
            notPrime[i * *j] = true;
            if (i % *j == 0) break;
        }
    }
    return;
}
int work(int n) {
    if (n > 0 && !notPrime[n]) return 1;
    if (n > 0 && (!notPrime[2 * n - 1] || !notPrime[2 * n + 1])) return 2;
    int ans;
    if (3 - prime[1] <= 2 * n && 2 * n <= prime[1] + 1)
        ans = prime[1];
    else {
        int l = 1, r = prime.size() - 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            (3 - prime[mid] <= 2 * n && 2 * n <= prime[mid] + 1) ? r = mid : l = mid;
        }
        ans = prime[r];
    }
    if (1 - prime[0] <= n && n <= prime[0])
        ans = min(ans, prime[0] * 2);
    else {
        int l = 0, r = prime.size() - 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            (1 - prime[mid] <= n && n <= prime[mid]) ? r = mid : l = mid;
        }
        ans = min(ans, prime[r] * 2);
    }
    return ans;
}

int main() {
    init();
    int _ = read<int>();
    while (_--) write(work(read<int>())), putch('\n');
    return 0;
}