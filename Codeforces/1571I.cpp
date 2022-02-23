/**
 * @file 1571I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

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

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

tiii a[maxn];
vector<int> answer;

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) get<0>(a[i]) = read<int>();
    for (int i = 1; i <= n; i++) get<1>(a[i]) = read<int>(), get<2>(a[i]) = i;
    sort(a + 1, a + n + 1);
    int l = 1, r = 1e9;
    while (l <= r) {
        int lim = (l + r) >> 1;
        answer.clear();
        priority_queue<pii, vector<pii>, greater<pii>> S;
        for (int i = 1, j = 1, p = lim; i <= n; i++, p++) {
            while (j <= n && get<0>(a[j]) <= p) S.emplace(get<1>(a[j]), get<2>(a[j])), j++;
            if (S.empty()) {
                l = lim + 1;
                break;
            }
            if (S.top().first < p) {
                r = lim - 1;
                break;
            }
            answer.push_back(S.top().second), S.pop();
        }
        if ((int)answer.size() == n) {
            l = lim;
            break;
        }
    }
    if ((int)answer.size() != n) return putstr("-1\n");
    write(l), putch('\n');
    for (auto i : answer) write(i), putch(' ');
    putch('\n');
    return;
}

bool mem2;

int main() {
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = read<int>();
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
#endif
    return 0;
}
