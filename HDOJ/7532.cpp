/**
 * @file 7532.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define maxn 100005

bool mem1;

struct Str {
    int type, x, k, id;
    int64_t h, num, baseh;
    bool operator<(const Str& o) const { return h < o.h; }
};

Str a[maxn];

struct Ptr {
    int id;
    bool operator<(const Ptr& o) const { return a[id].h < a[o.id].h; }
    bool operator>(const Ptr& o) const { return a[id].h > a[o.id].h; }
};

priority_queue<Ptr, vector<Ptr>, greater<Ptr>> strs;
queue<Ptr> wait;

void solve(void) {
    int n;
    cin >> n;
    int64_t mul = 1, damage = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].type >> a[i].h, a[i].num = 1, a[i].baseh = a[i].h;
        if (a[i].type == 2) cin >> a[i].x >> a[i].k;
        mul += (a[i].type == 3);
    }
    for (int i = 2; i <= n; i++) strs.push(Ptr{i});

    auto kill = [&](Str& s) {
        if (s.type == 3) return mul--, void();
        if (s.type == 2) {
            if (!s.x) return s.num = 0, void();
            return s.num++, s.x--, s.baseh <<= 1, s.h = damage + s.baseh, void();
        }
        damage += mul, void();
        vector<Ptr> cache;
        while (!strs.empty() && a[strs.top().id].h <= damage) {
            int p = strs.top().id;
            strs.pop();
            if (a[p].type == 3) {
                mul--;
                continue;
            }
            cache.push_back(Ptr{p});
        }
        sort(cache.begin(), cache.end(), [&](Ptr x, Ptr y) { return x.id < y.id; });
        for (auto i : cache) wait.push(i);
        return;
    };

    a[1].h = 0, kill(a[1]);
    while (!wait.empty()) {
        int p = wait.front().id;
        wait.pop();
        kill(a[p]);
        if (a[p].h > damage) strs.push(Ptr{p});
    }

    for (int i = 1; i <= n; i++) {
        a[i].h = max((int64_t)0, a[i].h - damage);
        if (a[i].type == 1) cout << a[i].h << endl;
        if (a[i].type == 2) {
            if (!a[i].num)
                cout << 0 << ' ';
            else {
                vector<int64_t> num;
                num.push_back(1);
                while (--a[i].num) {
                    const int lim = 1e8;
                    for (int j = 0; j < (int)num.size(); j++) num[j] *= a[i].k;
                    for (int j = 0; j + 1 < (int)num.size(); j++) num[j + 1] += num[j] / lim, num[j] %= lim;
                    while (num.back() >= lim) num.push_back(num.back() / lim), num[(int)num.size() - 2] %= lim;
                }
                cout << num.back();
                for (int j = (int)num.size() - 2; ~j; j--) {
                    char c[8];
                    for (int t = 0; t < 8; t++) c[t] = num[j] % 10 + '0', num[j] /= 10;
                    for (int t = 7; ~t; t--) cout << c[t];
                }
                cout << ' ';
            }
            cout << a[i].x << ' ' << a[i].h << endl;
        }
        if (a[i].type == 3) cout << a[i].h << endl;
    }

    while (!strs.empty()) strs.pop();
    while (!wait.empty()) wait.pop();
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}