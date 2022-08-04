/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 * @brief
 *      My solution: https://macesuted.moe/article/lg5068
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

#define maxn 100005
#define maxm 1000005
#define maxlgn 20

typedef pair<int, int> pii;

struct Ask {
    int l, r, tim;
};

int a[maxn];
Ask ask[maxm];

int ST[maxn][maxlgn], lg[maxn];
vector<int> f[maxn];
vector<pii> changes;

int tree[maxn];
void add(int p, int val) {
    for (register int i = p; i < maxn; i += i & -i) tree[i] += val;
    return;
}
long long sum(int p) {
    long long sum = 0;
    for (register int i = p; i; i -= i & -i) sum += tree[i];
    return sum;
}

int main() {
    int n = read<int>(), m = read<int>(), cnt = 0;
    memset(a, 0x3f, sizeof(a));
    for (register int i = 1; i <= m; i++)
        if (read<int>() == 1) {
            int x = read<int>();
            a[x] = min(a[x], i);
        } else {
            cnt++;
            ask[cnt].l = read<int>(), ask[cnt].r = read<int>(), ask[cnt].tim = i;
        }
    for (register int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (register int i = 1; i <= n; i++) ST[i][0] = a[i];
    for (register int i = 0; i + 1 <= lg[n]; i++)
        for (register int j = 1; j <= n; j++)
            ST[j][i + 1] = min(ST[j][i], (j + (1 << i) <= n) ? ST[j + (1 << i)][i] : 0x3f3f3f3f);
    for (register int i = 1; i <= n; i++) {
        f[i].resize(n / i + 2, 0);
        for (register int j = 0; j * i + 1 <= n; j++) {
            int l = j * i + 1, r = (j + 1) * i;
            if (j) f[i][j] = f[i][j - 1];
            f[i][j] = max(f[i][j],
                          min(ST[l][lg[i]], (r - (1 << lg[i]) + 1 > n) ? 0x3f3f3f3f : ST[r - (1 << lg[i]) + 1][lg[i]]));
            changes.push_back((pii){f[i][j], i});
        }
    }
    sort(changes.begin(), changes.end());
    for (register int i = 1, j = 0; i <= cnt; i++) {
        while (j < (int)changes.size() && changes[j].first <= ask[i].tim) add(changes[j++].second, 1);
        write(sum(ask[i].r) - sum(ask[i].l - 1) + (ask[i].r - ask[i].l + 1)), putch('\n');
    }
    return 0;
}