#include <bits/stdc++.h>
using namespace std;

namespace io {
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
    char c = getch();
    while (isspace(c)) c = getch();
    Il--;
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
}  // namespace io
using io::buftop;
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

bool mem1;

#define maxn 100005
#define maxlgn 20

typedef pair<int, int> pii;

class Trie {
   private:
    struct Node {
        int siz, cnt2k;
        long long sum;
        Node* son[2];
        Node(void) { son[0] = son[1] = NULL, siz = sum = cnt2k = 0; }
    };

    Node* root;
    Node buf[6000000];
    int tail;

    Node* newNode(void) { return &(buf[tail++] = Node()); }
    void pushUp(Node* p) {
        p->siz = p->sum = p->cnt2k = 0;
        if (p->son[0] != NULL) p->siz += p->son[0]->siz, p->sum += p->son[0]->sum << 1, p->cnt2k += p->son[0]->cnt2k;
        if (p->son[1] != NULL) p->siz += p->son[1]->siz, p->sum += (p->son[1]->sum << 1) + p->son[1]->siz;
        return;
    }
    void insert(Node*& p, int dep, int v) {
        if (p == NULL) p = newNode();
        if (dep == maxlgn) return p->siz++, p->cnt2k++, void();
        insert(p->son[v >> dep & 1], dep + 1, v);
        return pushUp(p);
    }
    void erase(Node*& p, int dep, int v) {
        p->siz--, p->cnt2k--;
        if (!p->siz) return p = NULL, void();
        if (dep == maxlgn) return;
        erase(p->son[v >> dep & 1], dep + 1, v);
        return pushUp(p);
    }
    void inc(Node* p) {
        if (p == NULL) return;
        swap(p->son[0], p->son[1]), inc(p->son[0]);
        return pushUp(p);
    }
    void dec(Node* p) {
        if (p == NULL) return;
        swap(p->son[0], p->son[1]), dec(p->son[1]);
        return pushUp(p);
    }
    long long getAns(Node* p) {
        if (p == NULL) return 0;
        return (p->son[1] == NULL ? 0 : ((p->son[1]->sum << 1) + p->son[1]->siz - p->son[1]->cnt2k) * 2) + getAns(p->son[0]);
    }

   public:
    Trie(void) { tail = 0, root = NULL; }
    void clear(void) { return tail = 0, root = NULL, void(); }
    void insert(int v) { return insert(root, 0, v); }
    void erase(int v) { return erase(root, 0, v); }
    void inc(void) { return inc(root); }
    void dec(void) { return dec(root); }
    long long getAns(void) { return root == NULL ? 0 : getAns(root->son[0]) + getAns(root->son[1]); }
} trie;

vector<vector<int>> graph;
int siz[maxn], v[maxn];
long long ans[maxn];
bool ban[maxn];

void calcSiz(int p, int pre = -1) {
    siz[p] = 1;
    for (auto i : graph[p])
        if (i != pre && !ban[i]) calcSiz(i, p), siz[p] += siz[i];
    return;
}
pii findCenter(int p, int tot, int pre = -1) {
    pii ans = {numeric_limits<int>::max(), p};
    int maxSon = 0;
    for (auto i : graph[p])
        if (i != pre && !ban[i]) ans = min(ans, findCenter(i, tot, p)), maxSon = max(maxSon, siz[i]);
    return min(ans, {max(maxSon, tot - siz[p]), p});
}
void insert(int p, int dist = 1, int pre = -1) {
    trie.insert(v[p] + dist - 1);
    for (auto i : graph[p])
        if (!ban[i] && i != pre) insert(i, dist + 1, p);
    return;
}
void erase(int p, int dist = 1, int pre = -1) {
    trie.erase(v[p] + dist - 1);
    for (auto i : graph[p])
        if (!ban[i] && i != pre) erase(i, dist + 1, p);
    return;
}
void calc(int p, int pre = -1) {
    trie.inc();
    ans[p] += trie.getAns();
    for (auto i : graph[p])
        if (!ban[i] && i != pre) calc(i, p);
    trie.dec();
    return;
}
void dfs(int p) {
    ban[p] = true;
    trie.clear();
    for (auto i : graph[p])
        if (!ban[i]) insert(i);
    trie.insert(v[p] - 1);
    ans[p] += trie.getAns();
    for (auto i : graph[p])
        if (!ban[i]) erase(i), calc(i), insert(i);
    for (auto i : graph[p])
        if (!ban[i]) calcSiz(i), dfs(findCenter(i, siz[i]).second);
    return;
}

void solve(void) {
    int n = read<int>();
    for (int i = 1; i <= n; i++) v[i] = read<int>();
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        graph[x].push_back(y), graph[y].push_back(x);
    }
    calcSiz(1), dfs(findCenter(1, siz[1]).second);
    for (int i = 1; i <= n; i++) write(ans[i]), putch(" \n"[i == n]);
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("team.in", "r", stdin), freopen("team.out", "w", stdout);
#endif
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
