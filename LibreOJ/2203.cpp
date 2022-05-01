/**
 * @file 2203.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

namespace IO {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
char iseoln(char c) { return c == '\n' || c == '\r'; }
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
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
string getline(const string& suf = "") {
    string s = suf;
    while (iseoln(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !iseoln(*Il) && *Il != EOF) Il++;
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
}  // namespace IO
using IO::getch;
using IO::getline;
using IO::getstr;
using IO::putch;
using IO::putstr;
using IO::read;
using IO::write;

bool mem1;

#define maxa3 343005

vector<vector<int>> graph, path[10];
vector<int> nodes;

int v[maxa3], vis[maxa3], dist[maxa3];
long long minVal = numeric_limits<long long>::max(), maxVal = numeric_limits<long long>::min(), sum = 0;

void dfs(int p) {
    if (!~p) return minVal = min(minVal, sum), maxVal = max(maxVal, sum), void();
    for (const auto& i : path[p]) {
        for (const auto& j : i)
            if (!vis[j]++) sum += v[j];
        dfs(p - 1);
        for (const auto& j : i)
            if (!--vis[j]) sum -= v[j];
    }
    return;
}

void solve(void) {
    int a = read<int>();
    graph.resize(a * a * a + 1);
    for (int i = 1, t; i <= a * a * a; i++) {
        if (!(v[i] = read<int>())) nodes.push_back(i);
        stringstream ssin(getline());
        graph[i].reserve(6);
        while (ssin >> t) graph[i].push_back(t);
    }
    int n = nodes.size();
    for (int i = 0; i < n; i++) {
        static queue<int> que;
        while (!que.empty()) que.pop();
        for (int j = 1; j <= a * a * a; j++) vis[j] = 0, dist[j] = numeric_limits<int>::max();
        vis[nodes[i]] = 1, dist[nodes[i]] = 0, que.push(nodes[i]);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (auto i : graph[p]) {
                if (dist[i] > dist[p] + 1) dist[i] = dist[p] + 1, vis[i] = 0, que.push(i);
                if (dist[i] == dist[p] + 1) vis[i] += vis[p];
            }
        }
        for (auto j : graph[nodes[i]]) {
            path[i].push_back(vector<int>()), path[i].back().push_back(nodes[i]);
            int p = j;
            while (true) {
                bool find = false;
                int tp = p;
                for (auto j : graph[p])
                    if (vis[j] == 1 && j != path[i].back().back()) {
                        p = j, find = true;
                        break;
                    }
                path[i].back().push_back(tp);
                if (!find) break;
            }
        }
        if (graph[nodes[i]].size() != 6) path[i].push_back(vector<int>());
    }
    for (int i = 1; i <= a * a * a; i++) vis[i] = 0;
    dfs(n - 1);
    write(minVal), putch(' '), write(maxVal), putch('\n');
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
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
