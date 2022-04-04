/**
 * @file 12946.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1;
int cache1[100], cache2[100];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
char iseoln(char c) { return c == '\n' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il && (fill(), 1), *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or && (flush(), 1), void(); }
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
    while (x) cache1[top++] = x % 10, x /= 10;
    while (top) putch(cache1[--top] ^ 48);
    return;
}
template <typename T>
void writeDouble(T x, int dep = 10) {
    if (x < 0) putch('-'), x = -x;
    int64_t fx = x;
    x -= fx;
    for (int i = 0; i < dep; i++) cache2[i] = (x *= 10), x -= int(x);
    if (int(x * 10) > 4) {
        cache2[dep - 1]++;
        for (int i = dep - 1; i; i--)
            if (cache2[i] == 10) cache2[i] = 0, cache2[i - 1]++;
        if (cache2[0] == 10) cache2[0] = 0, fx++;
    }
    write(fx), putch('.');
    for (int i = 0; i < dep; i++) putch(cache2[i] ^ 48);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
    }
    return s;
}
string getline(const string& suf = "") {
    string s = suf;
    while (iseoln(buftop())) getch();
    for (char* p = Il; Il != Ir; fill(), p = Il) {
        while (Il < Ir && !iseoln(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
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
using IO::getline;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;
using IO::writeDouble;

bool mem1;

#define maxn 100005
#define maxlgw 20

class Trie {
   private:
    struct Node {
        Node* son[2];
        int siz;
        Node(void) { son[0] = son[1] = NULL, siz = 0; }
    };

    Node* root;
    map<int, int> S;
    multiset<int> ans;

    int getSiz(Node* p) { return p == NULL ? 0 : p->siz; }
    void pushUp(Node* p) { return p->siz = getSiz(p->son[0]) + getSiz(p->son[1]), void(); }
    void insert(Node*& p, int l, int r, int qp, int qv) {
        if (p == NULL) p = new Node();
        if (l == r) {
            if (p->siz == 1) ans.erase(ans.find(S[qp])), S.erase(qp);
            if (!p->siz++) ans.insert(S[qp] = qv);
            return;
        }
        int mid = (l + r) >> 1, t = (qp > mid);
        !t ? insert(p->son[0], l, mid, qp, qv) : insert(p->son[1], mid + 1, r, qp, qv);
        if (getSiz(p->son[!t]) == 1) {
            int x = S.lower_bound(t ? l : mid + 1)->first;
            if (S[x] > (x ^ qp)) ans.erase(ans.find(S[x])), ans.insert(S[x] = x ^ qp);
        }
        return pushUp(p);
    }
    void split(Node* p, int l, int r) {
        if (p == NULL) return;
        if (l == r) {
            for (int i = 0; i < p->siz; i++) insert(l);
            return;
        }
        int mid = (l + r) >> 1;
        split(p->son[0], l, mid), split(p->son[1], mid + 1, r);
        return;
    }
    int ask(Node* p, int dep, int v) {
        if (p == NULL) return numeric_limits<int>::max();
        if (!~dep) return 0;
        int t = (v >> dep & 1);
        return p->son[t] == NULL ? (1 << dep) | ask(p->son[!t], dep - 1, v) : ask(p->son[t], dep - 1, v);
    }

   public:
    Trie(void) { root = NULL; }
    void insert(int v) { return insert(root, 0, (1 << maxlgw) - 1, v, ask(v)); }
    void merge(Trie* o) { return split(o->root, 0, (1 << maxlgw) - 1), delete o, void(); }
    int ask(int v) { return ask(root, maxlgw - 1, v); }
    int getAns(void) { return ans.empty() ? 0 : *ans.rbegin(); }
    void print(void) {
        for (auto i : S) cerr << i.first << ' ' << i.second << '#';
        cerr << endl;
        return;
    }
};

vector<vector<int>> graph;
int w[maxn], siz[maxn], son[maxn], ans[maxn];

void dfs1(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != pre) {
            dfs1(i, p), siz[p] += siz[i];
            if (!son[p] || siz[i] > siz[son[p]]) son[p] = i;
        }
    return;
}
Trie* dfs2(int p, int pre = -1) {
    Trie* trie = (son[p] ? dfs2(son[p], p) : new Trie());
    trie->insert(w[p]);
    for (auto i : graph[p])
        if (i != pre && i != son[p]) trie->merge(dfs2(i, p));
    ans[p] = (siz[p] == 1 ? -1 : trie->getAns());
    return trie;
}

void solve(void) {
    int n = read();
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) w[i] = read();
    for (int i = 1; i < n; i++) {
        int x = read(), y = read();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    dfs1(1), delete dfs2(1);
    for (int i = 1; i <= n; i++) write(ans[i]), putch('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("game.in", "r", stdin), freopen("game.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
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
