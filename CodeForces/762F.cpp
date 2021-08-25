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

#define maxn 1005
#define maxm 15
#define mod 1000000007

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

vector<vector<int> > S, T;

long long f[maxn][maxm];
int sons[maxn];
int n, m;

inline long long Mod(int x) { return x >= mod ? x - mod : x; }

void build(int p, int pre = -1) {
    sons[p] = 0;
    for (vector<int>::iterator i = T[p].begin(); i != T[p].end(); i++)
        if (*i != pre) sons[p] |= 1 << *i, build(*i, p);
    return;
}

void dfs(vector<vector<int> >& graph, int p, int pre = -1) {
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) dfs(graph, *i, p);
    static long long g[2][1 << maxm];
    memset(g[0], 0, sizeof(g[0]));
    g[0][0] = 1;
    int cnt = 0;
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) {
            cnt = !cnt;
            memset(g[cnt], 0, sizeof(g[cnt]));
            for (register int j = 0; j < (1 << m); j++)
                if (g[!cnt][j]) {
                    g[cnt][j] = Mod(g[cnt][j] + g[!cnt][j]);
                    for (register int k = 0; k < m; k++)
                        if (!(j >> k & 1))
                            g[cnt][j ^ (1 << k)] = (g[cnt][j ^ (1 << k)] + g[!cnt][j] * f[*i][k]) % mod;
                }
        }
    for (register int i = 0; i < m; i++) f[p][i] = g[cnt][sons[i]];
    return;
}

int main() {
    n = read<int>();
    S.resize(n);
    for (register int i = 1; i < n; i++) {
        int x = read<int>() - 1, y = read<int>() - 1;
        S[x].push_back(y), S[y].push_back(x);
    }
    m = read<int>();
    T.resize(m);
    for (register int i = 1; i < m; i++) {
        int x = read<int>() - 1, y = read<int>() - 1;
        T[x].push_back(y), T[y].push_back(x);
    }
    long long answer = 0, down = 0;
    for (register int root = 0; root < m; root++) {
        build(root);
        dfs(S, 0);
        for (register int i = 0; i < n; i++) answer = Mod(answer + f[i][root]);
    }
    for (register int root = 0; root < m; root++) {
        build(root);
        dfs(T, 0);
        for (register int i = 0; i < m; i++) down = Mod(down + f[i][root]);
    }
    write(answer * Pow(down, mod - 2) % mod), putch('\n');
    return 0;
}