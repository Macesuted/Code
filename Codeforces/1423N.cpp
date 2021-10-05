/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
#define SIZE (1 << 20)
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
inline void flush(void) { return fwrite(obuf, 1, oS - obuf, stdout), oS = obuf, void(); }
inline char getch(void) { return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++); }
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

#define maxn 12505
#define maxm 1000005

typedef pair<int, int> pii;

vector<vector<pii> > graph;

int from[maxm], to[maxm];
int v[maxn], w[maxm], val[maxn];
bool vis[maxm << 1];

int main() {
    int n = read<int>(), k = read<int>();
    graph.resize(n + 1);
    for (register int i = 1; i <= k; i++) {
        from[i] = read<int>(), to[i] = read<int>(), w[i] = 1, val[from[i]]++, val[to[i]]++;
        graph[max(from[i], to[i])].push_back((pii){min(from[i], to[i]), i});
    }
    for (register int i = 1; i <= n; i++) {
        for (vector<pii>::iterator j = graph[i].begin(); j != graph[i].end(); j++) {
            if (!v[j->first]) v[j->first]++, w[j->second]--, val[i]--;
            vis[val[j->first]] = true;
        }
        for (vector<pii>::iterator j = graph[i].begin(); j != graph[i].end() && vis[val[i]]; j++)
            v[j->first]--, w[j->second]++, val[i]++;
        for (vector<pii>::iterator j = graph[i].begin(); j != graph[i].end(); j++) vis[val[j->first]] = false;
    }
    static vector<int> answer;
    answer.clear();
    for (register int i = 1; i <= n; i++)
        if (v[i]) answer.push_back(i);
    write((int)answer.size()), putch('\n');
    for (vector<int>::iterator i = answer.begin(); i != answer.end(); i++) write(*i), putch(' ');
    if (!answer.empty()) putch('\n');
    for (register int i = 1; i <= k; i++) write(from[i]), putch(' '), write(to[i]), putch(' '), write(w[i]), putch('\n');
    return 0;
}