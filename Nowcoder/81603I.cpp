/**
 * @file 81603I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache[100];
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 0), void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') (c == '-') && (f = -f), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) return putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) cache[top++] = x % 10, x /= 10;
    while (top) putch(cache[--top] ^ 48);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace IO
using IO::read;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int> tiiii;

class SegmentTree2 {
   private:
    struct Node {
        int lMax, rMin;
        bool err;
        Node(void) { lMax = INT_MIN, rMin = INT_MAX, err = false; }
    };

    Node tree[maxn << 2];
    int n;

    void pushUp(int p) {
        tree[p].lMax = max(tree[p << 1].lMax, tree[p << 1 | 1].lMax);
        tree[p].rMin = min(tree[p << 1].rMin, tree[p << 1 | 1].rMin);
        tree[p].err = (tree[p << 1].err || tree[p << 1 | 1].err || tree[p << 1].lMax > tree[p << 1 | 1].rMin);
        return;
    }
    void updateL(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p].lMax = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? updateL(p << 1, l, mid, qp, v) : updateL(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void updateR(int p, int l, int r, int qp, int v) {
        if (l == r) return tree[p].rMin = v, void();
        int mid = (l + r) >> 1;
        qp <= mid ? updateR(p << 1, l, mid, qp, v) : updateR(p << 1 | 1, mid + 1, r, qp, v);
        return pushUp(p);
    }
    void clear(int p, int l, int r) {
        if (tree[p].lMax == INT_MIN && tree[p].rMin == INT_MAX) return;
        if (l == r) return tree[p].lMax = INT_MIN, tree[p].rMin = INT_MAX, void();
        int mid = (l + r) >> 1;
        clear(p << 1, l, mid), clear(p << 1 | 1, mid + 1, r);
        return pushUp(p);
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void updateL(int p, int v) { return updateL(1, 1, n, p, v); }
    void updateR(int p, int v) { return updateR(1, 1, n, p, v); }
    bool getErr(void) { return tree[1].err; }
    void clear(void) { return clear(1, 1, n); }
} ST2;

int delt[maxn];
class SegmentTree1 {
   private:
    vector<tiii> ops[maxn << 2];
    int n;

    void update(int p, int l, int r, int v0, int v1, int v2, int t) {
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (v0 <= mid)
            ops[p].emplace_back(v1, v2, t), update(p << 1, l, mid, v0, v1, v2, t);
        else
            ops[p].emplace_back(-v1, v2, t), update(p << 1 | 1, mid + 1, r, v0, v1, v2, t);
        return;
    }
    void solve(int p, int l, int r, tiiii a[]) {
        if (l == r) return;
        int mid = (l + r) >> 1;
        solve(p << 1, l, mid, a), solve(p << 1 | 1, mid + 1, r, a);
        ST2.clear();
        for (int i = l; i <= mid; i++) ST2.updateL(get<1>(a[i]), get<2>(a[i]));
        for (int i = mid + 1; i <= r; i++) ST2.updateR(get<1>(a[i]), get<2>(a[i]));
        delt[1] += ST2.getErr();
        for (int i = 0, prev = ST2.getErr(); i < (int)ops[p].size(); i++) {
            auto [v1, v2, t] = ops[p][i];
            v1 > 0 ? ST2.updateL(v1, v2) : ST2.updateR(-v1, v2);
            int curr = ST2.getErr();
            delt[t] += curr - prev;
            prev = curr;
        }
        return;
    }

   public:
    void resize(int _n) { return ST2.resize(n = _n), void(); }
    void update(tiiii v, int t) { return update(1, 1, n, get<0>(v), get<1>(v), get<2>(v), t); }
    void solve(tiiii a[]) { return solve(1, 1, n, a); }
} ST1;

tiiii a[maxn], b[maxn];
int pos[maxn];

void solve(void) {
    int n = read(), m = read();
    for (int i = 1; i <= n; i++) get<0>(a[i]) = read();
    for (int i = 1; i <= n; i++) get<1>(a[i]) = read();
    for (int i = 1; i <= n; i++) get<2>(a[i]) = read();
    for (int i = 1; i <= n; i++) get<3>(a[i]) = i;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) pos[get<3>(a[i])] = i, b[i] = a[i];
    ST1.resize(n);
    for (int i = 1; i <= m; i++) {
        int x = pos[read()], y = pos[read()];
        swap(get<2>(a[x]), get<2>(a[y]));
        ST1.update(a[x], i), ST1.update(a[y], i);
    }
    ST1.solve(b);
    for (int i = 1; i <= m; i++) cout << ((delt[i] += delt[i - 1]) ? "No" : "Yes") << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
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