/**
 * @file seq.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-02
 *
 * @copyright Copyright (c) 2022
 * @brief
 *      Time Limit: 1S  Memory Limit: 512M
 *
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
T read(void) {
    char c = getchar();
    T f = +1, x = 0;
    while (!('0' <= c && c <= '9')) {
        if (c == '-') f = -f;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x == 0) return putchar(x ^ 48), void();
    if (x > 9) write(x / 10);
    return putchar((x % 10) ^ 48), void();
}

bool mem1;

#define maxn 700005
#define maxm 1000005
#define maxlgm 22
#define maxq 100005
#define mod 998244353

typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

struct Node {
    long long lazy, sum;
    Node *son[2];
    Node(void) { son[0] = son[1] = NULL, lazy = sum = 0; }
};
Node *root;
Node heap[maxn];
int tail = 0;

int x[maxn], v[maxn], lg2[maxm], lowbit[maxm], val[maxlgm], ans[maxq];
tiii a[maxq];

void update(Node *p, int v, int size) {
    return p->lazy = (p->lazy + v) % mod, p->sum = (p->sum + 1LL * v * size) % mod, void();
}
Node *newNode(void) {
    if (tail >= maxn) tail -= maxn;
    heap[tail] = Node();
    return &heap[tail++];
}

void solve(void) {
    int n = read<int>(), m = read<int>(), q = read<int>();
    for (int i = 1; i <= n; i++) x[i] = read<int>(), v[i] = read<int>();
    for (int i = 1; i <= q; i++) get<0>(a[i]) = read<int>(), get<1>(a[i]) = read<int>(), get<2>(a[i]) = i;
    sort(a + 1, a + q + 1);
    Node *p = root = newNode();
    for (int i = maxlgm - 1; ~i; i--) p->sum = 1, p->son[0] = newNode(), p->son[1] = newNode(), p = p->son[0];
    p->lazy = p->sum = 1;
    for (int t = 1, j = 1; t <= n; t++) {
        long long sum = 0;
        for (int i = 0; i < maxlgm; i++) val[i] = 0;
        for (int i = x[t]; i; i -= lowbit[i])
            sum = (sum + 1LL * lowbit[i] * (val[lg2[lowbit[i]]] = (1LL * i * (i ^ v[t]) % mod))) % mod;
        p = root;
        Node *nroot = newNode(), *np = nroot;
        stack<Node *> sta;
        for (int i = maxlgm - 1; ~i; i--) {
            sta.push(np), np->son[0] = newNode(), np->son[1] = newNode();
            if (np->lazy) update(np->son[0], np->lazy, 1 << i), update(np->son[1], np->lazy, 1 << i), np->lazy = 0;
            if (x[t] >> i & 1) {
                update(np->son[0], p->son[0]->sum * val[i] % mod, 1 << i);
                update(np->son[1], p->son[1]->sum * val[i] % mod, 1 << i);
                swap(p->son[0], p->son[1]);
                sum = (sum + mod - (1LL << i) * val[i] % mod) % mod;
            }
            int b = (p->son[0]->son[0] == NULL);
            update(np->son[!b], p->son[!b]->lazy * sum % mod, 1 << i);
            p = p->son[b], np = np->son[b];
        }
        while (!sta.empty()) np = sta.top(), sta.pop(), np->sum = (np->son[0]->sum + np->son[1]->sum) % mod;
        root = nroot;
        while (j <= q && get<0>(a[j]) == t) {
            p = root;
            for (int i = maxlgm - 1; ~i; i--) {
                int b = get<1>(a[j]) >> i & 1;
                if (p->son[b] == NULL) break;
                p = p->son[b];
            }
            ans[get<2>(a[j])] = p->lazy;
            j++;
        }
    }
    for (int i = 1; i <= q; i++) write(ans[i]), putchar('\n');
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("seq.in", "r", stdin), freopen("seq.out", "w", stdout);
#endif
#ifdef MACESUTED
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    for (int i = 2; i < maxm; i++) lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i < maxm; i++) lowbit[i] = i & -i;

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
}