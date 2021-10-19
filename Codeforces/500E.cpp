/**
 * @file 500E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2021-10-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) {
    return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
}
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

bool mem1;

#define maxn 200005

struct pii {
    int first, second, id;
    inline bool operator<(const pii& oth) const {
        return pair<int, int>{this->first, this->first} < pair<int, int>{oth.first, oth.second};
    }
};

class FenwickTree {
   private:
    int tree[maxn];

   public:
    void add(int p, int v) {
        for (int i = p; i < maxn; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
};

FenwickTree BIT;

pair<int, int> a[maxn];
vector<vector<pair<int, int>>> ques;
int ans[maxn];
set<pii> S;

void insert(int l, int r, int id) {
    while (!S.empty() && S.begin()->first <= r) {
        r = max(r, S.begin()->second);
        BIT.add(S.begin()->id, S.begin()->first - S.begin()->second);
        S.erase(S.begin());
    }
    S.insert((pii){l, r, id}), BIT.add(id, r - l);
    return;
}
int query(int l, int r) {
    auto i = --S.lower_bound({r + 1, 0});
    return r - l - BIT.sum(i->id - 1) - min(i->second - i->first, r - i->first);
}
void solve(void) {
    int n = read<int>();
    ques.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int p = read<int>(), l = read<int>();
        a[i] = {p, p + l};
    }
    int q = read<int>();
    for (int i = 1; i <= q; i++) {
        int l = read<int>(), r = read<int>();
        ques[l].emplace_back(r, i);
    }
    for (int l = n; l; l--) {
        insert(a[l].first, a[l].second, l);
        for (auto i : ques[l]) ans[i.second] = query(a[l].first, a[i.first].second);
    }
    for (int i = 1; i <= q; i++) write(ans[i]), putch('\n');
    return;
}

bool mem2;

int main() {
    clock_t t1 = clock();
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024.0 / 1024.0 << "MB" << endl;

    int _ = 1;
    while (_--) solve();

    clock_t t2 = clock();
    cerr << "Time: " << (t2 - t1) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}