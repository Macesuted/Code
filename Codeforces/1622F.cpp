/**
 * @file 1622F.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

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

bool mem1;

#define maxn 10000005

vector<int> prime;
int bef[maxn];
unsigned long long v[maxn], h[maxn];
set<int> banned;

void print(int n) {
    cout << n - banned.size() << endl;
    for (int i = 1; i <= n; i++)
        if (banned.find(i) == banned.end()) cout << i << ' ';
    cout << endl;
    return;
}

void solve(void) {
    int n = read<int>();
    mt19937_64 rnd(time(NULL));
    for (int i = 2; i <= n; i++) {
        if (!bef[i]) prime.push_back(i), bef[i] = i, v[i] = rnd();
        for (auto j = prime.begin(); j != prime.end() && i * *j <= n; j++) {
            bef[i * *j] = *j;
            if (i % *j == 0) break;
        }
    }
    h[1] = 0;
    for (int i = 2; i <= n; i++) {
        h[i] = h[i - 1];
        int p = i;
        while (p != 1) h[i] ^= v[bef[p]], p /= bef[p];
    }
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) sum ^= h[i];
    if (sum == 0) return print(n);
    unordered_map<unsigned long long, int> S;
    for (int i = 1; i <= n; i++) {
        if ((sum ^ h[i]) == 0) return banned.insert(i), print(n);
        S.emplace(sum ^ h[i], i);
    }
    for (int i = 1; i <= n; i++) {
        if (S.find(h[i]) != S.end())
            return banned.insert(i), banned.insert(S[h[i]]), print(n);
    }
    return banned.insert(2), banned.insert(n / 2), banned.insert(n), print(n);
}

bool mem2;

int main() {
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
