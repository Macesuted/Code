/**
 * @file perm.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-04
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 2S  Memory Limit: 1G
 *
 */

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
T read(void) {
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

#define maxS 3628805
#define maxn 11
#define maxm 35
#define mod 998244353

#define fir first
#define sec second

typedef pair<int, int> pii;

string S[maxS];
vector<pii> lim[maxn][maxn];
int f[maxS], p[maxn], g[maxn], c[maxn];

int calc(string& s) {
    int ans = 0;
    for (int i = 1; i < (int)s.size(); i++) {
        c[i] = 0;
        for (int j = 0; j < i; j++)
            if (s[i] < s[j]) c[i]++;
        ans += c[i] * g[i];
    }
    return ans;
}

void solve(void) {
    int n = read<int>(), m = read<int>(), nS = 0;
    for (int i = 1; i <= m; i++) {
        int a = read<int>() - 1, b = read<int>() - 1, c = read<int>() - 1, d = read<int>() - 1;
        lim[c][d].emplace_back(a, b);
    }
    g[0] = 1;
    for (int i = 1; i <= n; i++) g[i] = g[i - 1] * i;
    for (int i = 0; i < n; i++) S[0].push_back('0' + i);
    do nS++, S[nS] = S[nS - 1];
    while (next_permutation(S[nS].begin(), S[nS].end()));
    f[0] = 1;
    for (int i = 0; i < nS; i++) {
        for (int j = 0; j < n; j++) p[S[i][j] - '0'] = j;
        int x = calc(S[i]);
        for (int j = 1; j < n; j++) {
            if (S[i][j - 1] > S[i][j]) continue;
            bool check = true;
            for (auto& x : lim[S[i][j - 1] - '0'][S[i][j] - '0'])
                if (p[x.fir] > p[x.sec]) {
                    check = false;
                    break;
                }
            if (!check) continue;
            int t = x + g[j];
            t -= c[j - 1] * g[j - 1] + c[j] * g[j];
            t += c[j - 1] * g[j] + c[j] * g[j - 1];
            assert(t < maxS);
            f[t] = (f[t] + f[x]) % mod;
        }
    }
    write(f[nS - 1]), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("perm.in", "r", stdin), freopen("perm.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
}