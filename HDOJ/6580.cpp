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

#define maxk 10005

typedef pair<int, int> pii;

map<int, set<pii>> S;
map<int, vector<long long>> go, back;
long long f[maxk], g[maxk], h[maxk];

int main() {
    int _ = read<int>();
    while (_--) {
        S.clear(), go.clear(), back.clear();
        int n = read<int>(), m = read<int>(), mid = (m + 1) / 2, k = read<int>();
        for (register int i = 1; i <= k; i++) {
            int x = read<int>(), y = read<int>(), t = read<int>();
            if (y < mid)
                S[x * 2].insert({mid - y, t});
            else
                S[x * 2 + 1].insert({y - mid, t});
        }
        f[0] = mid - 1, g[0] = 0;
        for (register int i = 1; i <= k; i++) f[i] = g[i] = 0x3f3f3f3f3f3f3f3f;
        for (auto i : S)
            if (i.first != 2) {
                int siz = i.second.size();
                vector<long long>&F = go[i.first], &G = back[i.first];
                F.resize(siz + 1), G.resize(siz + 1);
                F[0] = 0, G[0] = 0;
                for (register int j = 1; j <= siz; j++) F[j] = G[j] = 0x3f3f3f3f3f3f3f3f;
                vector<int> milk;
                for (auto j : i.second) {
                    milk.push_back(j.second);
                    for (auto j = milk.rbegin(); j + 1 != milk.rend() && *j < *(j + 1); j++) swap(*j, *(j + 1));
                    long long sum = 0;
                    int cnt = 0;
                    for (auto k : milk) {
                        cnt++, sum += k;
                        F[cnt] = min(F[cnt], j.first + sum);
                        G[cnt] = min(G[cnt], 2 * j.first + sum);
                    }
                }
            }
        for (auto i = S.begin(); i != S.end(); i++) {
            if (i->first == 2) continue;
            int dist = mid - 1 + i->first / 2 - 1;
            if (i->first % 2 == 0 && S.find(i->first + 1) != S.end()) {
                int lSiz = i->second.size(), rSiz = S[i->first + 1].size();
                vector<long long>&LF = go[i->first], &LG = back[i->first],
                            &RF = go[i->first + 1], &RG = back[i->first + 1];

                for (register int j = 0; j <= k; j++) h[j] = g[j];
                for (register int j = 1; j <= lSiz; j++)
                    for (register int t = k; t >= j; t--)
                        h[t] = min(h[t], g[t - j] + LG[j]);
                for (register int j = 0; j <= rSiz; j++)
                    for (register int t = k; t >= j; t--)
                        f[t] = min(f[t], dist + h[t - j] + RF[j]);

                for (register int j = 0; j <= k; j++) h[j] = g[j];
                for (register int j = 1; j <= rSiz; j++)
                    for (register int t = k; t >= j; t--)
                        h[t] = min(h[t], g[t - j] + RG[j]);
                for (register int j = 0; j <= lSiz; j++)
                    for (register int t = k; t >= j; t--)
                        f[t] = min(f[t], dist + h[t - j] + LF[j]);

                for (register int j = 0; j <= k; j++) h[j] = g[j];
                for (register int j = 1; j <= lSiz; j++)
                    for (register int t = k; t >= j; t--)
                        g[t] = min(g[t], h[t - j] + LG[j]);
                for (register int j = 0; j <= k; j++) h[j] = g[j];
                for (register int j = 1; j <= rSiz; j++)
                    for (register int t = k; t >= j; t--)
                        g[t] = min(g[t], h[t - j] + RG[j]);
                i++;
            } else {
                int siz = i->second.size();
                vector<long long>&F = go[i->first], &G = back[i->first];
                for (register int j = 0; j <= k; j++) h[j] = g[j];
                for (register int j = 1; j <= siz; j++)
                    for (register int t = k; t >= j; t--)
                        f[t] = min(f[t], dist + h[t - j] + F[j]), g[t] = min(g[t], h[t - j] + G[j]);
            }
        }
        for (auto i : S)
            if (i.first == 2) {
                int siz = i.second.size();
                vector<long long> F;
                F.resize(siz + 1), F[0] = 0;
                for (register int j = 1; j <= siz; j++) F[j] = 0x3f3f3f3f3f3f3f3f;
                vector<int> milk;
                for (auto j = i.second.rbegin(); j != i.second.rend(); j++) {
                    milk.push_back(j->second);
                    for (auto j = milk.rbegin(); j + 1 != milk.rend() && *j < *(j + 1); j++) swap(*j, *(j + 1));
                    long long sum = 0;
                    int cnt = 0;
                    for (auto k : milk) {
                        cnt++, sum += k;
                        F[cnt] = min(F[cnt], mid - j->first - 1 + sum);
                    }
                }
                for (auto t : i.second)
                    for (register int j = k; j; j--)
                        f[j] = min(f[j], f[j - 1] + t.second);
                for (register int i = 0; i <= siz; i++) f[i] = min(f[i], F[i]);
            } else
                break;
        for (register int i = 1; i <= k; i++) write(f[i]), putch(" \n"[i == k]);
    }
    return 0;
}