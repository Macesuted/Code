/**
 * @file 6109.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-11
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

#define maxn 50005
#define maxq 500005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int, int> tiiiii;

vector<tiii> rec[2][maxn];
long long ans[maxq];

class SegmentTree1 {
   private:
    class SegmentTree {
       private:
        struct Node {
            long long maxVal, maxVal_, lazy, lazy_;
            bool clearHist;
        };

        Node tree[maxn << 4];
        int n;

        void clearHist(int p) {
            if (tree[p].lazy_ || tree[p].lazy)
                calcLazy(p << 1, tree[p].lazy_, tree[p].lazy), calcLazy(p << 1 | 1, tree[p].lazy_, tree[p].lazy);
            return tree[p].maxVal_ = tree[p].maxVal, tree[p].lazy_ = tree[p].lazy = 0, tree[p].clearHist = true, void();
        }
        void calcLazy(int p, long long lazy_, long long lazy) {
            return tree[p].maxVal_ = max(tree[p].maxVal_, tree[p].maxVal + lazy_), tree[p].maxVal += lazy,
                   tree[p].lazy_ = max(tree[p].lazy_, tree[p].lazy + lazy_), tree[p].lazy += lazy, void();
        }
        void pushDown(int p) {
            if (tree[p].clearHist) clearHist(p << 1), clearHist(p << 1 | 1), tree[p].clearHist = false;
            if (tree[p].lazy_ || tree[p].lazy)
                calcLazy(p << 1, tree[p].lazy_, tree[p].lazy), calcLazy(p << 1 | 1, tree[p].lazy_, tree[p].lazy),
                    tree[p].lazy_ = tree[p].lazy = 0;
            return;
        }
        void pushUp(int p) {
            return tree[p].maxVal = max(tree[p << 1].maxVal, tree[p << 1 | 1].maxVal),
                   tree[p].maxVal_ = max(tree[p << 1].maxVal_, tree[p << 1 | 1].maxVal_), void();
        }
        void add(int p, int l, int r, int ql, int qr, long long v) {
            if (ql <= l && r <= qr) return calcLazy(p, max(0LL, v), v);
            pushDown(p);
            int mid = (l + r) >> 1;
            if (ql <= mid) add(p << 1, l, mid, ql, qr, v);
            if (qr > mid) add(p << 1 | 1, mid + 1, r, ql, qr, v);
            return pushUp(p);
        }
        void clearHist(int p, int l, int r, int ql, int qr) {
            if (ql <= l && r <= qr) return clearHist(p);
            pushDown(p);
            int mid = (l + r) >> 1;
            if (ql <= mid) clearHist(p << 1, l, mid, ql, qr);
            if (qr > mid) clearHist(p << 1 | 1, mid + 1, r, ql, qr);
            return pushUp(p);
        }

        long long getHistMaxVal(int p, int l, int r, int ql, int qr) {
            if (ql <= l && r <= qr) return tree[p].maxVal_;
            pushDown(p);
            int mid = (l + r) >> 1;
            if (qr <= mid) return getHistMaxVal(p << 1, l, mid, ql, qr);
            if (ql > mid) return getHistMaxVal(p << 1 | 1, mid + 1, r, ql, qr);
            return max(getHistMaxVal(p << 1, l, mid, ql, qr), getHistMaxVal(p << 1 | 1, mid + 1, r, ql, qr));
        }

       public:
        void resize(int _n) { return n = _n, void(); }
        void add(int l, int r, long long v) { return add(1, 1, n, l, r, v); }
        void clearHist(int l, int r) { return clearHist(1, 1, n, l, r); }
        long long getHistMaxVal(int l, int r) { return getHistMaxVal(1, 1, n, l, r); }
    } ST;

    struct Node {
        vector<tiii> whole, init;
        vector<tiiiii> query;
    };

    Node tree[maxn << 2];
    int n;

    void insRec(int p, int l, int r, int ql, int qr, tiii v) {
        if (ql <= l && r <= qr) return tree[p].whole.push_back(v);
        int mid = (l + r) >> 1;
        if (ql <= mid && mid <= qr) tree[p].init.push_back(v);
        if (ql <= mid) insRec(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insRec(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    void insQues(int p, int l, int r, tiiiii ques) {
        int mid = (l + r) >> 1;
        if ((l <= get<0>(ques) && get<0>(ques) <= mid && mid < get<1>(ques) && get<1>(ques) <= r) || l == r)
            return tree[p].query.push_back(ques);
        return get<1>(ques) <= mid ? insQues(p << 1, l, mid, ques) : insQues(p << 1 | 1, mid + 1, r, ques);
    }
    void solve(int p, int l, int r) {
        if (l == r) {
            for (auto i : tree[p].whole) ST.add(get<0>(i), get<1>(i), get<2>(i));
            ST.clearHist(1, n);
            for (auto i : tree[p].query) ans[get<4>(i)] = max(ans[get<4>(i)], ST.getHistMaxVal(get<2>(i), get<3>(i)));
            for (auto i : tree[p].whole) ST.add(get<0>(i), get<1>(i), -get<2>(i));
            return;
        }
        for (auto i : tree[p].whole) ST.add(get<0>(i), get<1>(i), get<2>(i));
        int mid = (l + r) >> 1;
        for (auto i : tree[p].init) ST.add(get<0>(i), get<1>(i), get<2>(i));
        static vector<tiii> cache;
        cache.clear(), ST.clearHist(1, n);
        sort(tree[p].query.begin(), tree[p].query.end(), [](tiiiii a, tiiiii b) { return get<0>(a) > get<0>(b); });
        auto j = tree[p].query.begin();
        while (j != tree[p].query.end() && get<0>(*j) == mid)
            ans[get<4>(*j)] = max(ans[get<4>(*j)], ST.getHistMaxVal(get<2>(*j), get<3>(*j))), j++;
        for (int i = mid - 1; i >= l; i--) {
            for (auto j : rec[0][i + 1])
                ST.add(get<0>(j), get<1>(j), -get<2>(j)), cache.emplace_back(get<0>(j), get<1>(j), -get<2>(j));
            for (auto j : rec[1][i]) ST.add(get<0>(j), get<1>(j), get<2>(j)), cache.push_back(j);
            while (j != tree[p].query.end() && get<0>(*j) == i)
                ans[get<4>(*j)] = max(ans[get<4>(*j)], ST.getHistMaxVal(get<2>(*j), get<3>(*j))), j++;
        }
        for (auto i = cache.rbegin(); i != cache.rend(); i++) ST.add(get<0>(*i), get<1>(*i), -get<2>(*i));
        cache.clear(), ST.clearHist(1, n);
        sort(tree[p].query.begin(), tree[p].query.end(), [](tiiiii a, tiiiii b) { return get<1>(a) < get<1>(b); });
        j = tree[p].query.begin();
        while (j != tree[p].query.end() && get<1>(*j) == mid)
            ans[get<4>(*j)] = max(ans[get<4>(*j)], ST.getHistMaxVal(get<2>(*j), get<3>(*j))), j++;
        for (int i = mid + 1; i <= r; i++) {
            for (auto j : rec[1][i - 1])
                ST.add(get<0>(j), get<1>(j), -get<2>(j)), cache.emplace_back(get<0>(j), get<1>(j), -get<2>(j));
            for (auto j : rec[0][i]) ST.add(get<0>(j), get<1>(j), get<2>(j)), cache.push_back(j);
            while (j != tree[p].query.end() && get<1>(*j) == i)
                ans[get<4>(*j)] = max(ans[get<4>(*j)], ST.getHistMaxVal(get<2>(*j), get<3>(*j))), j++;
        }
        for (auto i = cache.rbegin(); i != cache.rend(); i++) ST.add(get<0>(*i), get<1>(*i), -get<2>(*i));
        for (auto i : tree[p].init) ST.add(get<0>(i), get<1>(i), -get<2>(i));
        solve(p << 1, l, mid), solve(p << 1 | 1, mid + 1, r);
        for (auto i : tree[p].whole) ST.add(get<0>(i), get<1>(i), -get<2>(i));
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insRec(int l, int r, tiii v) { return insRec(1, 1, n, l, r, v); }
    void insQues(tiiiii ques) { return insQues(1, 1, n, ques); }
    void solve(void) { return ST.resize(n), solve(1, 1, n); }
} ST;

void solve(void) {
    ios::sync_with_stdio(false);
    int n = read<int>(), m = read<int>(), q = read<int>();
    ST.resize(n);
    for (int i = 1; i <= m; i++) {
        int l1 = read<int>(), r1 = read<int>(), l2 = read<int>(), r2 = read<int>(), x = read<int>();
        rec[0][l1].emplace_back(r1, r2, x), rec[1][l2].emplace_back(r1, r2, x), ST.insRec(l1, l2, {r1, r2, x});
    }
    for (int i = 1; i <= q; i++) {
        int l1 = read<int>(), r1 = read<int>(), l2 = read<int>(), r2 = read<int>();
        ST.insQues({l1, l2, r1, r2, i});
    }
    ST.solve();
    for (int i = 1; i <= q; i++) write(ans[i]), putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}
