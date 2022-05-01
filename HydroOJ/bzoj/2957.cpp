/**
 * @file 2957.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
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
}  // namespace IO
using IO::getch;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

struct Frac {
    int x, y;
    Frac(int x_ = 0, int y_ = 1) { *this = pii{x_, y_}; }
    bool operator<(const Frac& oth) const { return 1LL * this->x * oth.y < 1LL * this->y * oth.x; }
    bool operator<=(const Frac& oth) const { return 1LL * this->x * oth.y <= 1LL * this->y * oth.x; }
    Frac& operator=(const pii& val) {
        tie(x, y) = val;
        int t = gcd(x, y);
        x /= t, y /= t;
        return *this;
    }
};

class SegmentTree {
   private:
    struct Node {
        Frac maxVal;
        int ans;
    };

    Node tree[maxn << 2];
    int n;

    void pushUp(int p, int l, int r) {
        int mid = (l + r) >> 1;
        tree[p].maxVal = max(tree[p << 1].maxVal, tree[p << 1 | 1].maxVal);
        tree[p].ans = tree[p << 1].ans + getAns(p << 1 | 1, mid + 1, r, tree[p << 1].maxVal);
        return;
    }
    void update(int p, int l, int r, int qp, Frac v) {
        if (l == r) return tree[p].maxVal = v, tree[p].ans = 1, void();
        int mid = (l + r) >> 1;
        qp <= mid ? update(p << 1, l, mid, qp, v) : update(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p, l, r);
    }
    int getAns(int p, int l, int r, Frac lim) {
        if (tree[p].maxVal <= lim) return 0;
        if (l == r) return tree[p].ans;
        int mid = (l + r) >> 1;
        if (tree[p << 1].maxVal <= lim) return getAns(p << 1 | 1, mid + 1, r, lim);
        return getAns(p << 1, l, mid, lim) + tree[p].ans - tree[p << 1].ans;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void update(int p, Frac v) { return update(1, 1, n, p, v); }
    int query(void) { return tree[1].ans; }
} ST;

void solve(void) {
    int n = read<int>(), m = read<int>();
    ST.resize(n);
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        ST.update(x, Frac(y, x));
        write(ST.query()), putch('\n');
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
