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

#define maxn 100005
#define maxlgn 20

int a[maxn];
bool sign[maxn];

class BIT {
   private:
    vector<int> tree;

    int n;

   public:
    void resize(int _n) { return tree.resize((n = _n + 1) + 1); }
    void add(int p, int delta) {
        p++;
        for (register int i = p; i <= n; i += i & -i) tree[i] += delta;
        return;
    }
    int sum(int p) {
        if (p < 0) return 0;
        p = min(p + 1, n);
        int sum = 0;
        for (register int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
};

namespace REAL {

vector<vector<int> > graph;
int fa[maxn][maxlgn], dep[maxn];

namespace BUILDVIRT {

int heav[maxn], siz[maxn];
void calcSize(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (!sign[i] && i != pre) calcSize(i, p), siz[p] += siz[i];
    return;
}
int root;
void findRoot(int p, int all, int pre = -1) {
    heav[p] = all - siz[p];
    for (auto i : graph[p])
        if (!sign[i] && i != pre) findRoot(i, all, p), heav[p] = max(heav[p], siz[i]);
    if (root == 0 || heav[p] < heav[root]) root = p;
    return;
}
inline int getRoot(int p) { return calcSize(p), root = 0, findRoot(p, siz[p]), root; }

}  // namespace BUILDVIRT
using BUILDVIRT::getRoot;

void INIT(int p, int pre = 0) {
    dep[p] = dep[fa[p][0] = pre] + 1;
    for (register int i = 1; i < maxlgn; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];
    for (auto i : graph[p])
        if (i != pre) INIT(i, p);
    return;
}
int dist(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int answer = 0;
    for (register int i = maxlgn - 1; ~i; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i], answer += 1 << i;
    if (x == y) return answer;
    for (register int i = maxlgn - 1; ~i; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i], answer += 1 << (i + 1);
    return answer + 2;
}

}  // namespace REAL

BIT tree[2][maxn];

int faRoot[maxn];

int dep1, dep2;
void dfs(int p, int root, int dist = 0, int pre = -1) {
    dep1 = max(dep1, dist);
    if (faRoot[root] != -1) dep2 = max(dep2, REAL::dist(p, faRoot[root]));
    for (auto i : REAL::graph[p])
        if (!sign[i] && i != pre) dfs(i, root, dist + 1, p);
    return;
}
void buildVirt(int p) {
    sign[p] = true;
    dep1 = dep2 = 0, dfs(p, p);
    tree[0][p].resize(dep1), tree[1][p].resize(dep2);
    for (auto i : REAL::graph[p])
        if (!sign[i]) {
            int child = REAL::getRoot(i);
            faRoot[child] = p;
            buildVirt(child);
        }
    return;
}

void update(int x, int y) {
    int p = x;
    while (p != -1) {
        tree[0][p].add(REAL::dist(x, p), y);
        if (faRoot[p] != -1) tree[1][p].add(REAL::dist(x, faRoot[p]), y);
        p = faRoot[p];
    }
    return;
}

int main() {
    // freopen("3730.log", "w", stderr);
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    REAL::graph.resize(n + 1);
    for (register int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        REAL::graph[x].push_back(y), REAL::graph[y].push_back(x);
    }
    REAL::INIT(1);
    int root = REAL::getRoot(1);
    faRoot[root] = -1, buildVirt(root);
    for (register int i = 1; i <= n; i++) update(i, a[i]);
    int lastans = 0;
    while (m--)
        if (read<int>() == 0) {
            int x = read<int>(), k = read<int>();
            x ^= lastans, k ^= lastans;
            int p = faRoot[x], pre = x, answer = tree[0][x].sum(k);
            while (p != -1) {
                int dis = REAL::dist(p, x);
                answer += tree[0][p].sum(k - dis) - tree[1][pre].sum(k - dis);
                pre = p, p = faRoot[p];
            }
            write(lastans = answer), putch('\n');
        } else {
            int x = read<int>(), y = read<int>();
            x ^= lastans, y ^= lastans;
            if (!(1 <= x && x <= n)) return 0;
            update(x, y - a[x]), a[x] = y;
        }
    return 0;
}