/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 * @brief
 *      My Tutorial: https://www.macesuted.cn/article/lg7447/
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

#define maxn 500005
#define blockLen 500

typedef pair<int, int> pii;

vector<pii> empty;

class SegmentTree {
   public:
    struct AnsType {
        long long sum;
        int minVal, maxVal;
        AnsType(void) { sum = 0, minVal = 0x3f3f3f3f, maxVal = 0; }
        AnsType(long long _sum, int _minVal, int _maxVal) { sum = _sum, minVal = _minVal, maxVal = _maxVal; }
        inline AnsType operator+(const AnsType& oth) const {
            return (AnsType){sum + oth.sum, min(minVal, oth.minVal), max(maxVal, oth.maxVal)};
        }
    };

   private:
    struct Node {
        int minVal, maxVal, size;
        long long sum, lazy;
        Node *l, *r;
        vector<pii> rec;
        Node(void) { l = r = NULL, minVal = 0x3f3f3f3f, maxVal = sum = lazy = size = 0; }
    };

    Node* root;
    int n;

    void update(Node* p, int l, int r, long long delta) {
        if (r - l + 1 <= blockLen) {
            for (vector<pii>::iterator i = p->rec.begin(); i != p->rec.end(); i++) i->second -= delta;
            return recalc(p, l, r);
        }
        p->lazy += delta, p->minVal -= delta, p->maxVal -= delta, p->sum -= p->size * delta;
        return;
    }
    void recalc(Node* p, int l, int r) {
        p->minVal = 0x3f3f3f3f, p->maxVal = 0, p->sum = 0, p->size = p->rec.size();
        for (vector<pii>::iterator i = p->rec.begin(); i != p->rec.end(); i++)
            p->sum += i->second, p->minVal = min(p->minVal, i->second), p->maxVal = max(p->maxVal, i->second);
        return;
    }
    void pushDown(Node* p, int l, int r) {
        if (p == NULL) return;
        if (!p->lazy) return;
        int mid = (l + r) >> 1;
        if (p->l != NULL) update(p->l, l, mid, p->lazy);
        if (p->r != NULL) update(p->r, mid + 1, r, p->lazy);
        p->lazy = 0;
        return;
    }
    inline void pushUp(Node* p) {
        p->minVal = 0x3f3f3f3f, p->maxVal = 0, p->sum = 0, p->size = 0;
        if (p->l != NULL)
            p->minVal = min(p->minVal, p->l->minVal), p->maxVal = max(p->maxVal, p->l->maxVal),
            p->sum += p->l->sum, p->size += p->l->size;
        if (p->r != NULL)
            p->minVal = min(p->minVal, p->r->minVal), p->maxVal = max(p->maxVal, p->r->maxVal),
            p->sum += p->r->sum, p->size += p->r->size;
        return;
    }
    void insert(Node*& p, int l, int r, int qp, int val) {
        if (p == NULL) p = new Node();
        if (r - l + 1 <= blockLen) {
            bool find = false;
            for (vector<pii>::iterator i = p->rec.begin(); !find && i != p->rec.end(); i++)
                if (i->first == qp) i->second = val, find = true;
            if (!find) p->rec.push_back((pii){qp, val});
            return recalc(p, l, r);
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        qp <= mid ? insert(p->l, l, mid, qp, val) : insert(p->r, mid + 1, r, qp, val);
        return pushUp(p);
    }
    void update(Node* p, int l, int r, int ql, int qr, long long val) {
        if (p == NULL) return;
        if (p->maxVal <= val) return;
        if (ql <= l && r <= qr && p->minVal > val) return update(p, l, r, val);
        if (r - l + 1 <= blockLen) {
            for (vector<pii>::iterator i = p->rec.begin(); i != p->rec.end(); i++)
                if (ql <= i->first && i->first <= qr && i->second > val) i->second -= val;
            return recalc(p, l, r);
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) update(p->l, l, mid, ql, qr, val);
        if (qr > mid) update(p->r, mid + 1, r, ql, qr, val);
        return pushUp(p);
    }
    AnsType getAns(Node* p, int l, int r, int ql, int qr) {
        if (p == NULL) return (AnsType){};
        if (ql <= l && r <= qr) return (AnsType){p->sum, p->minVal, p->maxVal};
        if (r - l + 1 <= blockLen) {
            AnsType ans = (AnsType){0, 0x3f3f3f3f, 0};
            for (vector<pii>::iterator i = p->rec.begin(); i != p->rec.end(); i++)
                if (ql <= i->first && i->first <= qr)
                    ans.sum += i->second, ans.minVal = min(ans.minVal, i->second), ans.maxVal = max(ans.maxVal, i->second);
            return ans;
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        AnsType answer;
        if (ql <= mid) answer = answer + getAns(p->l, l, mid, ql, qr);
        if (qr > mid) answer = answer + getAns(p->r, mid + 1, r, ql, qr);
        return answer;
    }
    void findEmpty(Node*& p, int l, int r, int limit) {
        if (p == NULL) return;
        if (p->minVal >= limit) return;
        if (r - l + 1 <= blockLen) {
            static vector<pii> cache;
            cache.clear();
            for (vector<pii>::iterator i = p->rec.begin(); i != p->rec.end(); i++)
                (i->second < limit ? empty : cache).push_back(*i);
            p->rec = cache;
            recalc(p, l, r);
            if (p->size == 0) delete p, p = NULL;
            return;
        }
        pushDown(p, l, r);
        int mid = (l + r) >> 1;
        findEmpty(p->l, l, mid, limit), findEmpty(p->r, mid + 1, r, limit);
        pushUp(p);
        if (p->size == 0) delete p, p = NULL;
        return;
    }

   public:
    SegmentTree(void) { root = NULL; }
    inline void resize(int _n) { return n = _n, void(); }
    inline void insert(int p, int val) { return insert(root, 1, n, p, val); }
    inline void update(int l, int r, long long delta) { return update(root, 1, n, l, r, delta); }
    inline AnsType getAns(int l, int r) { return getAns(root, 1, n, l, r); }
    inline void findEmpty(int limit) { return findEmpty(root, 1, n, limit); }
};

SegmentTree tree[8];
long long pow14[8];

int log14(int x) {
    int t = 0;
    while (t < 7 && pow14[t + 1] <= x) t++;
    return t;
}

int main() {
    pow14[0] = 1;
    for (register int i = 1; i < 8; i++) pow14[i] = pow14[i - 1] * 14;
    int n = read<int>(), m = read<int>();
    for (register int i = 0; i < 8; i++) tree[i].resize(n);
    for (register int i = 1, t; i <= n; i++) {
        t = read<int>();
        tree[log14(t)].insert(i, t);
    }
    int lastans = 0;
    while (m--) {
        if (read<int>() == 1) {
            int l = read<int>(), r = read<int>(), x = read<int>();
            l ^= lastans, r ^= lastans, x ^= lastans;
            for (register int i = 0; i < 8; i++) tree[i].update(l, r, x), tree[i].findEmpty(1 << (2 * i));
            for (vector<pii>::iterator i = empty.begin(); i != empty.end(); i++)
                tree[log14(i->second)].insert(i->first, i->second);
            empty.clear();
        } else {
            int l = read<int>(), r = read<int>();
            l ^= lastans, r ^= lastans;
            SegmentTree::AnsType answer;
            for (register int i = 0; i < 8; i++) answer = answer + tree[i].getAns(l, r);
            write(answer.sum), putch(' '), write(answer.minVal), putch(' '), write(answer.maxVal), putch('\n');
            lastans = answer.sum & ((1 << 20) - 1);
        }
    }
    return 0;
}