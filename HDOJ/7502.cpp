/**
 * @file 7502.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define maxn 500005

int64_t TIME;

struct Func {
    mutable int64_t k, b;

    Func(void) : k(0), b(0) {}
    Func(int64_t _k, int64_t _b) : k(_k), b(_b) {}

    int64_t getVal(void) const { return k * TIME + b; }

    bool operator<(const Func& o) const { return getVal() < o.getVal() || (getVal() == o.getVal() && k < o.k); }
    Func operator+(const Func& o) const { return Func(k + o.k, b + o.b); }
    Func operator-(const Func& o) const { return Func(k - o.k, b - o.b); }
    Func& operator+=(const Func& o) { return *this = *this + o; }
    Func& operator-=(const Func& o) { return *this = *this - o; }
};

int64_t t[maxn], l[maxn], r[maxn];

multiset<Func> S;
set<pair<int64_t, Func>> opTim;
Func ans;

int64_t cross(Func a, Func b) { return (b.b - a.b + 1) / 2; }

void insertL(set<Func>::iterator p) {
    if (p == S.begin()) return;
    auto q = p;
    q--;
    opTim.emplace(cross(*q, *p), *q);
    return;
}
void eraseL(set<Func>::iterator p) {
    if (p == S.begin()) return;
    auto q = p;
    q--;
    opTim.erase({cross(*q, *p), *q});
    return;
}
void insertR(set<Func>::iterator p) {
    auto q = p;
    q++;
    if (q == S.end()) return;
    opTim.emplace(cross(*p, *q), *p);
    return;
}
void eraseR(set<Func>::iterator p) {
    auto q = p;
    q++;
    if (q == S.end()) return;
    opTim.erase({cross(*p, *q), *p});
    return;
}

void print(void) {
    cerr << "PRINT " << TIME << endl;
    for (auto [k, b] : S) cerr << '(' << k << ',' << b << ',' << k * TIME + b << ')';
    cerr << endl;
    for (auto [tim, Func] : opTim) cerr << "(" << tim << ' ' << Func.k << ' ' << Func.b << ')';
    cerr << endl;
    cerr << ans.k << ' ' << ans.b << ' ' << ans.getVal() + S.size() / 2 << endl;
    return;
}

void insert(int l, int r) {
    auto pl = S.lower_bound({-1, l + TIME});
    if (pl == S.end()) return;
    if (pl->getVal() > r) {
        if (pl->k == -1) return;
        auto it = S.emplace(+1, l - 1 - TIME);
        it = S.emplace(-1, r + 1 + TIME);
        insertL(it);
        ans += Func{+1, l - 1 - TIME};
        ans -= Func{-1, r + 1 + TIME};
        return;
    }
    auto pr = --S.lower_bound({-1, r + 1 + TIME});
    if (pl->k == +1) eraseR(pl), ans -= *pl, pl->b = l - 1 - TIME, ans += *pl, insertR(pl), pl++;
    if (pr->k == -1)
        eraseL(pr), ans += *pr, pr->b = r + 1 + TIME, ans -= *pr, insertL(pr);
    else
        pr++;
    for (auto i = pl; i != pr;) {
        eraseL(i);
        ans += *i, i = S.erase(i);
        eraseR(i);
        ans -= *i, i = S.erase(i);
        if (i != S.end()) insertL(i);
    }
    return;
}

void update(set<pair<int64_t, Func>>::iterator it) {
    auto p = S.find(it->second);
    ans -= *p, p = S.erase(p);
    ans += *p, p = S.erase(p);
    opTim.erase(it);
    return;
}

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> t[i] >> l[i] >> r[i];
    TIME = 0, S.clear(), S.insert({-1, 0}), S.insert({+1, 0}), opTim.clear(), opTim.emplace(t[n + 1] = INT64_MAX, Func{0, 0});
    ans = Func(2, 0);
    for (int i = 1, j = 1; i <= q; i++) {
        int64_t qt;
        cin >> qt;
        while (min(t[j], opTim.begin()->first) <= qt) {
            if (j <= n && t[j] < opTim.begin()->first)
                TIME = t[j], insert(l[j], r[j]), j++;
            else
                TIME = opTim.begin()->first - 1, update(opTim.begin());
        }
        TIME = qt;
        cout << ans.getVal() + S.size() / 2 << ' ';
    }
    cout << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}