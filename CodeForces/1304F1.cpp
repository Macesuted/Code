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

#define maxn 55
#define maxm 20005

class SegmentTree {
   private:
    long long tree[maxm << 2], lazy[maxm << 2];
    int n;

    inline void pushDown(int p) {
        if (!lazy[p]) return;
        tree[p << 1] += lazy[p], tree[p << 1 | 1] += lazy[p];
        lazy[p << 1] += lazy[p], lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
        return;
    }
    void update(int p, int l, int r, int ql, int qr, long long val) {
        if (ql <= l && r <= qr) return tree[p] += val, lazy[p] += val, void();
        pushDown(p);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p << 1, l, mid, ql, qr, val);
        if (qr > mid) update(p << 1 | 1, mid + 1, r, ql, qr, val);
        return tree[p] = max(tree[p << 1], tree[p << 1 | 1]), void();
    }
    long long query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        pushDown(p);
        int mid = (l + r) >> 1;
        long long answer = 0;
        if (ql <= mid) answer = max(answer, query(p << 1, l, mid, ql, qr));
        if (qr > mid) answer = max(answer, query(p << 1 | 1, mid + 1, r, ql, qr));
        return answer;
    }

   public:
    inline void resize(int tn) { return n = tn, void(); }
    inline void update(int l, int r, long long val) { return update(1, 1, n, l, r, val); }
    inline long long query(int l, int r) { return query(1, 1, n, l, r); }
};

SegmentTree tree;

int a[maxn][maxm];
long long f[maxn][maxm], sum[maxn][maxm];

int main() {
    int n = read<int>(), m = read<int>(), k = read<int>();
    for (register int i = 1; i <= n; i++)
        for (register int j = 1; j <= m; j++)
            sum[i][j] = sum[i][j - 1] + (a[i][j] = read<int>());
    for (register int l = 1; l + k - 1 <= m; l++) {
        int r = l + k - 1;
        f[1][l] = sum[1][r] - sum[1][l - 1];
    }
    tree.resize(m - k + 1);
    for (register int i = 2; i <= n; i++) {
        for (register int j = 1; j + k - 1 <= m; j++)
            tree.update(j, j, f[i - 1][j] + sum[i][min(m, j + k - 1)] - sum[i][j - 1] - tree.query(j, j));
        for (register int j = 1; j < k; j++)
            tree.update(max(1, j - k + 1), min(m - k + 1, j), -a[i][j]);
        for (register int l = 1; l + k - 1 <= m; l++) {
            int r = l + k - 1;
            if (l > 1) tree.update(max(1, l - k), min(m - k + 1, l - 1), a[i][l - 1]);
            tree.update(max(1, r - k + 1), min(m - k + 1, r), -a[i][r]);
            f[i][l] = tree.query(1, m - k + 1) + sum[i][r] - sum[i][l - 1];
        }
    }
    long long answer = 0;
    for (register int i = 1; i + k - 1 <= m; i++) answer = max(answer, f[n][i]);
    write(answer), putch('\n');
    return 0;
}