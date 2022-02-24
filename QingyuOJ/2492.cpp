/**
 * @file 2492.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 3S  Memory Limit: 64M
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

#define maxn 17
#define MOD 1145

class Hashlist {
   private:
    struct Node {
        long long key, val;
        int nxt;
    };

    Node heap[1005];

   public:
    int list[MOD], cnt;

    Hashlist() {
        cnt = 0;
        for (int i = 0; i < MOD; i++) list[i] = 0;
        return;
    }
    void insert(long long key, long long val) {
        int x = key % MOD;
        heap[++cnt].key = key, heap[cnt].val = val, heap[cnt].nxt = list[x], list[x] = cnt;
        return;
    }
    long long ask(long long key) {
        for (register int p = list[key % MOD]; p; p = heap[p].nxt)
            if (heap[p].key == key) return heap[p].val;
        return -1;
    }
} ha;

int n;
long long maxS, mod, rec[105], X[maxn * 2], vS1[1 << 7], vS2[1 << 7], vS3[1 << 19], vC1[1 << 7], vC2[1 << 7], vC3[1 << 19];
vector<int> S1, S2, S3;

long long R(long long S) { return (S >> 1) | ((long long)(S & 1) << (2 * n - 1)); }
long long calcB(long long A) {
    long long B = 0;
    for (int t = 0; t < n; t++) B |= (long long)((A >> t & 1) ^ (A >> (2 * t + 1) & 1)) << t;
    for (int t = n; t < 2 * n; t++) B |= (long long)((A >> t & 1) ^ (A >> (4 * n - 2 * t - 2) & 1)) << t;
    return B;
}

void solve(void) {
    n = read<int>();
    long long H = read<long long>(), max1S = (1LL << n) - 1, max2S = max1S << n;
    maxS = (1LL << (2 * n)) - 1, mod = (1LL << (2 * n - 1)) - 1;
    for (int i = 0; i < 2 * n; i++) {
        X[i] = calcB(1LL << i);
        X[i] = X[i] ^ R(X[i]);
        if (!X[i]) continue;
        vector<int> pos;
        for (int j = 0; j < 2 * n; j++)
            if (X[i] >> j & 1) pos.push_back(j);
        if (pos.back() < n)
            S1.push_back(i);
        else if (pos.front() >= n)
            S2.push_back(i);
        else
            S3.push_back(i);
    }
    int S1z = S1.size(), S2z = S2.size(), S3z = S3.size();
    for (int i = 0; i < (1 << S1z); i++) {
        vS1[i] = 0;
        for (int t = 0; t < S1z; t++)
            if (i >> t & 1) vS1[i] |= 1LL << S1[t], vC1[i] ^= X[S1[t]];
    }
    for (int i = 0; i < (1 << S2z); i++) {
        vS2[i] = 0;
        for (int t = 0; t < S2z; t++)
            if (i >> t & 1) vS2[i] |= 1LL << S2[t], vC2[i] ^= X[S2[t]];
    }
    for (int i = 0; i < (1 << S3z); i++) {
        vS3[i] = 0;
        for (int t = 0; t < S3z; t++)
            if (i >> t & 1) vS3[i] |= 1LL << S3[t], vC3[i] ^= X[S3[t]];
    }
    for (int i = 0; i < (1 << S3z); i++) {
        for (int j = 0; j < (1 << S2z); j++) {
            long long A = vS3[i] | vS2[j], C = (vC2[j] ^ vC3[i]) & max2S;
            ha.insert(rec[j] = (H + mod - (239LL * A + 153LL * C) % mod) % mod, A);
        }
        for (int j = 0; j < (1 << S1z); j++) {
            long long A = vS1[j], C = (vC1[j] ^ vC3[i]) & max1S;
            auto p = ha.ask((239 * A + 153 * C) % mod);
            if (p != -1) return write(p | A), putch('\n');
        }
        for (int j = 0; j < (1 << S2z); j++) ha.list[rec[j] % MOD] = 0;
        ha.cnt = 0;
    }
    return putstr("No Solution!\n");
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
