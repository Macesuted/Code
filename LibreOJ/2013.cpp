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

#define maxn 20005
#define maxlgn 18
#define maxlgv 60

class Basis {
   public:
    long long a[maxlgv];

    Basis(void) {
        memset(a, 0, sizeof(a));
    }
    void insert(long long val) {
        for (register int i = maxlgv - 1; ~i && val; i--)
            if (val >> i & 1)
                if (a[i])
                    val ^= a[i];
                else {
                    for (register int j = i - 1; ~j; j--)
                        if (val >> j & 1) val ^= a[j];
                    for (register int j = maxlgv - 1; j > i; j--)
                        if (a[j] >> i & 1) a[j] ^= val;
                    return a[i] = val, void();
                }
        return;
    }
    long long getAns(void) {
        long long answer = 0;
        for (register int i = maxlgv - 1; ~i; i--)
            if (!(answer >> i & 1)) answer ^= a[i];
        return answer;
    }

    inline Basis operator+(Basis oth) {
        Basis ans = *this;
        for (register int i = 0; i < maxlgv; i++)
            if (oth.a[i]) ans.insert(oth.a[i]);
        return ans;
    }
};

long long fa[maxn][maxlgn];
Basis g[maxn][maxlgn];
long long a[maxn];
int dep[maxn];

vector<vector<int> > graph;

void dfs(int p, int pre = 0) {
    dep[p] = dep[pre] + 1, fa[p][0] = pre, g[p][0].insert(a[pre]);
    for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1], g[p][i] = g[p][i - 1] + g[fa[p][i - 1]][i - 1];
    for (vector<int>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (*i != pre) dfs(*i, p);
    return;
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (register int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (register int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int jump(int p, int step) {
    for (register int i = maxlgn - 1; ~i; i--)
        if (step >> i & 1) p = fa[p][i];
    return p;
}

int main() {
    int n = read<int>(), q = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i <= n; i++) a[i] = read<long long>();
    for (register int i = 1, from, to; i < n; i++) {
        from = read<int>(), to = read<int>();
        graph[from].push_back(to), graph[to].push_back(from);
    }
    dfs(1);
    while (q--) {
        int x = read<int>(), y = read<int>(), t = lca(x, y);
        Basis ans;
        if (x != t) {
            int l = 0;
            while (dep[fa[x][l + 1]] >= dep[t]) l++;
            ans = ans + g[x][l] + g[jump(x, dep[x] - dep[t] - (1 << l))][l];
        }
        if (y != t) {
            int l = 0;
            while (dep[fa[y][l + 1]] >= dep[t]) l++;
            ans = ans + g[y][l] + g[jump(y, dep[y] - dep[t] - (1 << l))][l];
        }
        ans.insert(a[x]), ans.insert(a[y]);
        write(ans.getAns()), putch('\n');
    }
    return 0;
}