/**
 * @file 5657.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 100005
#define mod 1000000007
#define e9 1000000001

typedef pair<int, int> pii;
typedef pair<int64_t, int> pIi;

map<int64_t, vector<pii>> rec;

int Mod(int x) { return x >= mod ? x - mod : x; }

class SegmentTree1 {
   private:
    class SegmentTree2 {
       private:
        struct Node {
            int l, r, sum, ans, ver;
            bool laz;
            Node(void) = default;
            Node(int ver_, int64_t ql, int64_t qr) {
                l = r = 0, ver = ver_, sum = min((int64_t)e9, qr - ql + 1);
                ans = __int128_t(ql + qr) * (qr - ql + 1) / 2 % mod, laz = false;
            }
        };

        Node T[maxn * 160];
        vector<int> roots;
        stack<int> nodes;
        queue<int> emp;
        int64_t n;
        int ver;

        int newNode(Node x) {
            assert(!emp.empty());
            int p = emp.front();
            emp.pop(), nodes.push(p), T[p] = x;
            return p;
        }
        void chk(int& p, int64_t l, int64_t r) {
            if (!p) p = newNode(Node(ver, l, r));
            if (T[p].ver != ver) p = newNode(T[p]), T[p].ver = ver;
            return;
        }
        void upd(int p) { return T[p].sum = T[p].ans = 0, T[p].laz = true, void(); }
        void pushDown(int p, int64_t l, int64_t r) {
            int64_t mid = (l + r) >> 1;
            chk(T[p].l, l, mid), chk(T[p].r, mid + 1, r);
            if (T[p].laz) upd(T[p].l), upd(T[p].r), T[p].laz = false;
            return;
        }
        void pushUp(int p) {
            return T[p].sum = min(e9, T[T[p].l].sum + T[T[p].r].sum), T[p].ans = Mod(T[T[p].l].ans + T[T[p].r].ans), void();
        }
        int64_t update(int& p, int64_t l, int64_t r, int64_t qp, int& x) {
            chk(p, l, r);
            if (qp <= l && x >= T[p].sum) {
                int64_t ret = T[p].ans;
                return x -= T[p].sum, upd(p), ret;
            }
            pushDown(p, l, r);
            int64_t mid = (l + r) >> 1, ans = 0;
            if (qp <= mid) ans = Mod(ans + update(T[p].l, l, mid, qp, x));
            if (x) ans = Mod(ans + update(T[p].r, mid + 1, r, qp, x));
            return pushUp(p), ans;
        }

       public:
        SegmentTree2(void) {
            for (int i = 1; i < maxn * 160; i++) emp.push(i);
            roots.push_back(0), ver = 0, n = 2e14;
            return;
        }
        void copy(void) { return ver++, roots.push_back(roots.back()); }
        void destroy(void) {
            while (!nodes.empty() && T[nodes.top()].ver == ver) emp.push(nodes.top()), nodes.pop();
            return ver--, roots.pop_back();
        }
        int64_t update(int64_t p, int x) { return update(roots.back(), 1, n, p, x); }
    } ST;

    vector<pIi> T[maxn << 2];
    int n;

    void insert(int p, int l, int r, int ql, int qr, pIi v) {
        if (ql <= l && r <= qr) return T[p].push_back(v);
        int mid = (l + r) >> 1;
        if (ql <= mid) insert(p << 1, l, mid, ql, qr, v);
        if (qr > mid) insert(p << 1 | 1, mid + 1, r, ql, qr, v);
        return;
    }
    void solve(int p, int l, int r, int64_t tot = 0) {
        ST.copy();
        for (auto i : T[p]) tot = Mod(tot + ST.update(i.first, i.second));
        if (l == r)
            cout << tot << endl;
        else {
            int mid = (l + r) >> 1;
            solve(p << 1, l, mid, tot), solve(p << 1 | 1, mid + 1, r, tot);
        }
        ST.destroy();
        return;
    }

   public:
    void resize(int _n) { return n = _n, void(); }
    void insert(int l, int r, pIi v) { return insert(1, 1, n, l, r, v); }
    void solve(void) { return solve(1, 1, n); }
} ST;

void solve(void) {
    int n;
    cin >> n, ST.resize(n);
    for (int i = 1; i <= n; i++) {
        int64_t d, b;
        cin >> d >> b, rec[d].emplace_back(i, b);
    }
    for (auto& [x, y] : rec)
        for (int j = 0; j < (int)y.size(); j++)
            ST.insert(y[j].first, (j == (int)y.size() - 1 ? n : y[j + 1].first - 1), {x, y[j].second});
    rec.clear();
    ST.solve();
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