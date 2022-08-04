/**
 * @file 7476.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
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

#define maxn 200005

class SegmentTree {
   private:
    struct Node {
        int maxVal;
        priority_queue<int, vector<int>, less<int>> heap;
        Node(void) { maxVal = -1; }
    };

    Node tree[maxn << 2];
    int n;

    int getTop(int p) { return tree[p].heap.empty() ? -1 : tree[p].heap.top(); }
    void pushUp(int p) {
        return tree[p].maxVal = max({tree[p << 1].maxVal, tree[p << 1 | 1].maxVal, getTop(p)}), void();
    }
    void insert(int p, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return tree[p].maxVal = max(tree[p].maxVal, v), tree[p].heap.push(v);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    void erase(int p, int l, int r, int ql, int qr, int v) {
        if (tree[p].maxVal < v) return;
        if (getTop(p) == v) {
            tree[p].heap.pop(), tree[p].maxVal = getTop(p);
            if (l == r) return;
            if (l < ql) insert(p, l, r, l, ql - 1, v);
            if (qr < r) insert(p, l, r, qr + 1, r, v);
            return pushUp(p);
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) erase(p << 1, l, mid, ql, qr, v);
        if (qr > mid) erase(p << 1 | 1, mid + 1, r, ql, qr, v);
        return pushUp(p);
    }
    int getAns(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].maxVal;
        int mid = (l + r) >> 1, ans = getTop(p);
        if (ql <= mid) ans = max(ans, getAns(p << 1, l, mid, ql, qr));
        if (qr > mid) ans = max(ans, getAns(p << 1 | 1, mid + 1, r, ql, qr));
        return ans;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int l, int r, int v) { return insert(1, 1, n, l, r, v); }
    void erase(int l, int r, int v) { return v == -1 ? void() : erase(1, 1, n, l, r, v); }
    int getAns(int l, int r) { return getAns(1, 1, n, l, r); }
} ST;

void solve(void) {
    int n = read<int>(), m = read<int>();
    ST.resize(n);
    while (m--) {
        int op = read<int>(), l = read<int>(), r = read<int>();
        if (op == 1)
            ST.insert(l, r, read<int>());
        else if (op == 2)
            ST.erase(l, r, ST.getAns(l, r));
        else
            write(ST.getAns(l, r)), putch('\n');
    }
    return;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
