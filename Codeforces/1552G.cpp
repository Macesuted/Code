/**
 * @file 1552G.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-22
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

#define maxk 15

long long S[maxk], T[maxk];
vector<long long> f[maxk];

void solve(void) {
    int n = read<int>(), k = read<int>();
    if (n == 1) return putstr("ACCEPTED\n");
    for (int i = 1; i <= k; i++) {
        int x = read<int>();
        while (x--) S[i] |= (1LL << (read<int>() - 1));
        T[i] = T[i - 1] | S[i];
    }
    if (T[k] != (1LL << n) - 1) return putstr("REJECTED\n");
    f[0].push_back(0);
    for (int i = 1; i <= k; i++) {
        long long U = (S[i] ^ T[i - 1]) & S[i], P = S[i] & T[i - 1];
        vector<int> bS;
        for (int l = 0; l < n; l++)
            if (S[i] >> l & 1) bS.push_back(l);
        int cU = __builtin_popcountll(U), ct = 0;
        f[i].resize((int)f[i - 1].size() * (cU + 1));
        for (auto j : f[i - 1]) {
            int cnt[2] = {0, 0};
            for (int l = 0; l < n; l++)
                if (P >> l & 1) cnt[j >> l & 1]++;
            long long x = j;
            for (int i = 0; i < cnt[0]; i++)
                if ((x >> bS[i] & 1) != 0) x ^= 1LL << bS[i];
            for (int i = cnt[0]; i < (int)bS.size(); i++)
                if ((x >> bS[i] & 1) != 1) x ^= 1LL << bS[i];
            f[i][ct++] = x;
            for (int k = 1; k <= cU; k++) f[i][ct++] = (x ^= 1LL << bS[cnt[0] + k - 1]);
        }
        sort(f[i].begin(), f[i].end()), f[i].resize(unique(f[i].begin(), f[i].end()) - f[i].begin());
    }
    if ((int)f[k].size() == n + 1) return putstr("ACCEPTED\n");
    return putstr("REJECTED\n");
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
