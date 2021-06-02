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

#define maxn 100005
#define maxlgn 10
#define mod 4001

class SegmentTree {
   private:
    struct Node {
        int pl[2], pr[2], answer, sum;
        Node(void) { pl[0] = pl[1] = pr[0] = pr[1] = answer = sum = 0; }
        inline Node operator+(const Node& oth) const {
            Node ans;
            ans.pl[0] = this->pl[0] + oth.pl[this->sum], ans.pl[1] = this->pl[1] + oth.pl[!this->sum];
            ans.pr[0] = this->pr[oth.sum] + oth.pr[0], ans.pr[1] = this->pr[!oth.sum] + oth.pr[1];
            ans.answer = (this->pr[0] * oth.pl[1] + this->pr[1] * oth.pl[0] + this->answer + oth.answer) % mod;
            ans.sum = this->sum ^ oth.sum;
            return ans;
        }
    };

    Node tree[maxn << 2];
    int n;

    void build(int p, int l, int r, int a[]) {
        if (l == r) {
            tree[p].pl[a[l] & 1] = 1, tree[p].pl[!(a[l] & 1)] = 0;
            tree[p].pr[a[l] & 1] = 1, tree[p].pr[!(a[l] & 1)] = 0;
            tree[p].sum = tree[p].answer = a[l] & 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a), build(p << 1 | 1, mid + 1, r, a);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    void update(int p, int l, int r, int qp, int val) {
        if (l == r) {
            tree[p].pl[val & 1] = 1, tree[p].pl[!(val & 1)] = 0;
            tree[p].pr[val & 1] = 1, tree[p].pr[!(val & 1)] = 0;
            tree[p].sum = tree[p].answer = val & 1;
            return;
        }
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, val) : update(p << 1 | 1, mid + 1, r, qp, val);
        return tree[p] = tree[p << 1] + tree[p << 1 | 1], void();
    }
    Node getAns(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p];
        int mid = (l + r) >> 1;
        Node answer;
        if (ql <= mid) answer = answer + getAns(p << 1, l, mid, ql, qr);
        if (qr > mid) answer = answer + getAns(p << 1 | 1, mid + 1, r, ql, qr);
        return answer;
    }

   public:
    inline void build(int tn, int a[]) { return build(1, 1, n = tn, a); }
    inline void update(int p, int val) { return update(1, 1, n, p, val); }
    inline int getAns(int l, int r) { return getAns(1, 1, n, l, r).answer; }
};

SegmentTree tree[maxlgn];
int a[maxn], b[maxn];

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<int>();
    for (register int i = 0; i < maxlgn; i++) {
        for (register int j = 1; j <= n; j++) b[j] = (a[j] >> i & 1);
        tree[i].build(n, b);
    }
    while (m--)
        if (read<int>() == 1) {
            int p = read<int>(), x = read<int>();
            for (register int i = 0; i < maxlgn; i++)
                if ((a[p] >> i & 1) != (x >> i & 1)) tree[i].update(p, x >> i & 1);
            a[p] = x;
        } else {
            int l = read<int>(), r = read<int>();
            int answer = 0;
            for (register int i = 0; i < maxlgn; i++) answer = (answer + (tree[i].getAns(l, r) << i)) % mod;
            write(answer), putch('\n');
        }
    return 0;
}