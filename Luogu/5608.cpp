/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 * @brief
 *      My tutorial: https://www.macesuted.cn/article/lg5608/
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
#define sqrtn 180
#define mod 1000000007
#define leafLen 60

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

inline int Mod(int x) { return x >= mod ? x - mod : x; }

class SegmentTree {
   private:
    struct Node {
        bool op, hasLazyOp, lazyOp, hasLazyNum;
        long long allMul, lMul, rMul;
        int allPlus, ans, lazyNum;
        int lNum, rNum, lLen, rLen;
        int midLenS[sqrtn], midLenL[maxn / sqrtn + 5], tail;
        Node *l, *r;
        Node(void) { hasLazyOp = hasLazyNum = false, l = r = NULL, clear(); }
        void clear(void) {
            memset(midLenS, 0, sizeof(midLenS));
            tail = 0;
            return;
        }
        void add(int val) {
            if (val == 0) return;
            if (val < sqrtn)
                midLenS[val]++;
            else
                midLenL[++tail] = val;
            return;
        }
        Node operator+(const Node& oth) const {
            Node a = *this, b = oth;
            a.hasLazyOp = a.hasLazyNum = false;
            a.allMul = a.allMul * b.allMul % mod;
            a.allPlus = Mod(a.allPlus + b.allPlus);
            a.rNum = b.rNum;
            for (register int i = 0; i < sqrtn; i++) a.midLenS[i] += b.midLenS[i];
            for (register int i = 1; i <= b.tail; i++) a.add(b.midLenL[i]);
            if (!a.op) {
                if (!a.lLen) swap(a.lLen, a.rLen), swap(a.lMul, a.rMul);
                if (!b.rLen) swap(b.lLen, b.rLen), swap(b.lMul, b.rMul);
                a.ans = Mod(Mod(a.ans + b.ans) + Mod(a.rMul + b.lMul));
                a.add(a.rLen), a.add(b.lLen);
                a.rLen = b.rLen, a.rMul = b.rMul;
            } else {
                if (!a.rLen) swap(a.lLen, a.rLen), swap(a.lMul, a.rMul);
                if (!b.lLen) swap(b.lLen, b.rLen), swap(b.lMul, b.rMul);
                int nLen = a.rLen + b.lLen, nMul = a.rMul * b.lMul % mod;
                a.ans = Mod(a.ans + b.ans);
                a.rLen = b.rLen, a.rMul = b.rMul;
                if (!a.lLen)
                    a.lLen = nLen, a.lMul = nMul;
                else if (!a.rLen)
                    a.rLen = nLen, a.rMul = nMul;
                else
                    a.ans = Mod(a.ans + nMul), a.add(nLen);
            }
            a.op = b.op;
            return a;
        }
        int getAns(void) {
            int ans = this->ans;
            if (lLen) ans = Mod(ans + lMul);
            if (rLen) ans = Mod(ans + rMul);
            return ans;
        }
    };

    Node* root;

    int a[maxn], op[maxn];

    int n;

    Node merge(Node* l, Node* r) {
        Node ans = *l + *r;
        ans.l = l, ans.r = r;
        return ans;
    }
    Node reCalc(int l, int r) {
        Node p;
        p.op = op[r], p.ans = 0;
        p.clear();
        p.lNum = a[l], p.rNum = a[r];
        p.lLen = 1, p.lMul = a[l], p.rLen = 0, p.rMul = 0;
        while (l + p.lLen <= r && op[l + p.lLen - 1]) p.lMul = p.lMul * a[l + p.lLen] % mod, p.lLen++;
        if (l + p.lLen - 1 < r) {
            p.rLen = 1, p.rMul = a[r];
            while (op[r - p.rLen]) p.rMul = p.rMul * a[r - p.rLen] % mod, p.rLen++;
            int tl = l + p.lLen, tr = r - p.rLen;
            if (tl <= tr) {
                long long last = a[tl];
                int lastPos = tl;
                for (register int i = tl; i < tr; i++)
                    if (op[i])
                        last = last * a[i + 1] % mod;
                    else
                        p.ans = Mod(p.ans + last), p.add(i - lastPos + 1), last = a[lastPos = i + 1];
                p.add(tr - lastPos + 1), p.ans = Mod(p.ans + last);
            }
        }
        p.allMul = 1, p.allPlus = 0;
        for (register int i = l; i <= r; i++) p.allMul = p.allMul * a[i] % mod, p.allPlus = Mod(p.allPlus + a[i]);
        return p;
    }
    void modifyNum(Node* p, int l, int r, int num) {
        if (r - l + 1 < leafLen) {
            for (register int i = l; i <= r; i++) a[i] = num;
            *p = reCalc(l, r);
            return;
        }
        p->allMul = Pow(num, r - l + 1), p->allPlus = 1LL * (r - l + 1) * num % mod, p->ans = 0;
        long long lastPow = 1;
        int lastPos = 0;
        for (register int i = 1; i < sqrtn; i++)
            if (p->midLenS[i])
                lastPow = lastPow * Pow(num, i - lastPos) % mod, lastPos = i,
                p->ans = Mod(p->ans + lastPow * p->midLenS[i] % mod);
        for (register int i = 1; i <= p->tail; i++) p->ans = Mod(p->ans + Pow(num, p->midLenL[i]));
        p->lNum = p->rNum = num;
        if (p->lLen) p->lMul = Pow(num, p->lLen);
        if (p->rLen) p->rMul = Pow(num, p->rLen);
        p->hasLazyNum = true, p->lazyNum = num;
        return;
    }
    inline void modifyOp(Node* p, int l, int r, bool _op) {
        if (r - l + 1 < leafLen) {
            for (register int i = l; i <= r; i++) op[i] = _op;
            *p = reCalc(l, r);
            return;
        }
        p->op = _op;
        if (!_op) {
            p->ans = Mod(Mod(p->allPlus + mod - p->lNum) + mod - p->rNum);
            p->lLen = 1, p->lMul = p->lNum;
            p->rLen = 1, p->rMul = p->rNum;
            p->clear(), p->midLenS[1] = r - l - 1;
        } else {
            p->ans = 0;
            p->lLen = r - l + 1, p->lMul = p->allMul;
            p->rLen = 0, p->rMul = 0;
            p->clear();
        }
        p->hasLazyOp = true, p->lazyOp = _op;
        return;
    }
    inline void pushDown(Node* p, int l, int r) {
        int mid = (l + r) >> 1;
        if (p->hasLazyOp) {
            p->hasLazyOp = false;
            modifyOp(p->l, l, mid, p->lazyOp), modifyOp(p->r, mid + 1, r, p->lazyOp);
        }
        if (p->hasLazyNum) {
            p->hasLazyNum = false;
            modifyNum(p->l, l, mid, p->lazyNum), modifyNum(p->r, mid + 1, r, p->lazyNum);
        }
        return;
    }
    void build(Node*& p, int l, int r, int _a[], bool _op[]) {
        if (p == NULL) p = new Node();
        if (r - l + 1 < leafLen) {
            for (register int i = l; i <= r; i++) a[i] = _a[i], op[i] = _op[i];
            *p = reCalc(l, r);
            return;
        }
        int mid = (l + r) >> 1;
        build(p->l, l, mid, _a, _op), build(p->r, mid + 1, r, _a, _op);
        *p = merge(p->l, p->r);
        return;
    }
    void updateNum(Node* p, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) return modifyNum(p, l, r, val);
        if (r - l + 1 < leafLen) {
            for (register int i = max(l, ql); i <= min(r, qr); i++) a[i] = val;
            *p = reCalc(l, r);
            return;
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) updateNum(p->l, l, mid, ql, qr, val);
        if (qr > mid) updateNum(p->r, mid + 1, r, ql, qr, val);
        *p = merge(p->l, p->r);
        return;
    }
    void updateOp(Node* p, int l, int r, int ql, int qr, bool _op) {
        if (ql <= l && r <= qr) return modifyOp(p, l, r, _op);
        if (r - l + 1 < leafLen) {
            for (register int i = max(l, ql); i <= min(r, qr); i++) op[i] = _op;
            *p = reCalc(l, r);
            return;
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) updateOp(p->l, l, mid, ql, qr, _op);
        if (qr > mid) updateOp(p->r, mid + 1, r, ql, qr, _op);
        *p = merge(p->l, p->r);
        return;
    }
    Node getAns(Node* p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return *p;
        if (r - l + 1 < leafLen) return reCalc(max(l, ql), min(r, qr));
        int mid = (l + r) >> 1;
        pushDown(p, l, r);
        if (qr <= mid) return getAns(p->l, l, mid, ql, qr);
        if (ql > mid) return getAns(p->r, mid + 1, r, ql, qr);
        return getAns(p->l, l, mid, ql, qr) + getAns(p->r, mid + 1, r, ql, qr);
    }

   public:
    SegmentTree(void) { root = NULL; }
    inline void resize(int _n) { return n = _n, void(); }
    inline void build(int a[], bool op[]) { return build(root, 1, n, a, op); }
    inline void updateNum(int l, int r, int val) { return updateNum(root, 1, n, l, r, val); }
    inline void updateOp(int l, int r, bool op) { return updateOp(root, 1, n, l, r, op); }
    inline int getAns(int l, int r) { return getAns(root, 1, n, l, r).getAns(); }
};

SegmentTree tree;

int a[maxn];
bool op[maxn];

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 1; i <= n; i++) a[i] = read<long long>() % mod;
    for (register int i = 1; i < n; i++) op[i] = read<int>();
    tree.resize(n), tree.build(a, op);
    while (m--) {
        int opt = read<int>();
        if (opt == 1) {
            int l = read<int>(), r = read<int>();
            tree.updateNum(l, r, read<long long>() % mod);
        } else if (opt == 2) {
            int l = read<int>(), r = read<int>();
            tree.updateOp(l, r, read<int>());
        } else {
            int l = read<int>(), r = read<int>();
            write(tree.getAns(l, r)), putch('\n');
        }
    }
    return 0;
}