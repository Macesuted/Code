/**
 * @file 1616E.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-01-20
 *
 * @copyright Copyright (c) 2022
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
void putch(char x) {
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
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
template <typename T>
T read() {
    T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    return x * f;
}
template <typename T>
void write(const T& t) {
    T x = t;
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

#define maxn 100005

class FenwickTree {
   private:
    vector<int> tree;
    int size;

   public:
    void resize(int _size) { return tree.resize((size = _size) + 1); }
    void clear(void) { return tree.clear(); }
    void add(int p, int v) {
        for (int i = p; i <= size; i += i & -i) tree[i] += v;
        return;
    }
    int sum(int p) {
        int sum = 0;
        for (int i = p; i; i -= i & -i) sum += tree[i];
        return sum;
    }
};

string a, b;
deque<int> pos[26];
FenwickTree dist;

long long solve(void) {
    int n = read<int>();
    a = " " + getstr(), b = " " + getstr();
    dist.resize(n);
    for (int i = 0; i < 26; i++) pos[i].clear();
    for (int i = 1; i <= n; i++) pos[a[i] - 'a'].push_back(i), dist.add(i, i > 1);
    long long ans = 0x3f3f3f3f3f3f3f3f, cost = 0;
    for (int i = 1; i <= n; i++) {
        int c = b[i] - 'a', near = -1;
        for (int j = 0; j < c; j++)
            if (pos[j].size() && (near == -1 || pos[j].front() < pos[near].front())) near = j;
        if (near != -1) ans = min(ans, cost + dist.sum(pos[near].front()));
        if (pos[c].size() && (near == -1 || pos[c].front() < pos[near].front())) near = c;
        if (near != c) break;
        cost += dist.sum(pos[c].front()), dist.add(pos[c].front() + 1, -1), pos[c].pop_front();
    }
    dist.clear();
    return ans == 0x3f3f3f3f3f3f3f3f ? -1 : ans;
}

bool mem2;

int main() {
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) write(solve()), putch('\n');

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
