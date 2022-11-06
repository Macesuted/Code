#include <bits/stdc++.h>
using namespace std;

template <typename T>
T read(void) {
    T f = 1, num = 0;
    char c = getchar();

    for (; !isdigit(c); c = getchar())
        if (c == '-') f = -f;

    for (; isdigit(c); c = getchar()) num = (num << 3) + (num << 1) + (c ^ 48);

    return f * num;
}

const int maxn = 1e5 + 5;

struct Edge {
    int to, dist;
};

int fa[maxn], dis[maxn];
int ringDist[maxn];
int ring[maxn], ringCnt = 0;
bool isRing[maxn];
int dfn[maxn], timet = 0;
long long dep[maxn];

vector<list<Edge>> graph;

long long A[maxn],  //前缀+子树最大深度
    B[maxn],        //前缀中两个子树的最大深度+两点距离
    C[maxn],        //后缀+子树最大深度
    D[maxn];        //后缀中两个子树的最大深度+两点距离

void dfs(int p) {
    dfn[p] = ++timet;

    for (list<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++)
        if (i->to != fa[p]) {
            if (!dfn[i->to]) {
                fa[i->to] = p;
                dis[i->to] = i->dist;
                dfs(i->to);
            } else if (dfn[i->to] > dfn[p]) {
                for (int to = i->to; to != p; to = fa[to]) {
                    isRing[to] = true;
                    ring[++ringCnt] = to;
                    ringDist[ringCnt] = dis[to];
                }

                isRing[p] = true;
                ring[++ringCnt] = p;
                ringDist[ringCnt] = i->dist;
            }
        }

    return;
}

long long ans = 0;

void work(int p, int fa) {
    for (list<Edge>::iterator i = graph[p].begin(); i != graph[p].end(); i++) {
        if (!isRing[i->to] && i->to != fa) {
            work(i->to, p);
            ans = max((long long)dep[p] + dep[i->to] + i->dist, ans);
            dep[p] = max(dep[p], dep[i->to] + i->dist);
        }
    }

    return;
}

int main() {
    int n = read<int>();
    graph.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        int from = read<int>(), to = read<int>(), dist = read<int>();
        graph[from].push_back((Edge){to, dist}), graph[to].push_back((Edge){from, dist});
    }

    dfs(1);

    for (int i = 1; i <= ringCnt; i++) work(ring[i], 0);

    long long sum = 0, maxx = 0;

    for (int i = 1; i <= ringCnt; i++) {
        sum += ringDist[i - 1];                           // sum是前缀
        A[i] = max(A[i - 1], dep[ring[i]] + sum);         //子树深度+前缀长度
        B[i] = max(B[i - 1], sum + maxx + dep[ring[i]]);  //用之前最深的+当前子树深度+前缀长度
        maxx = max(maxx, dep[ring[i]] - sum);             //维护最深的子树深度
    }

    sum = maxx = 0;
    int tmp = ringDist[ringCnt];
    ringDist[ringCnt] = 0;

    for (int i = ringCnt; i; i--) {
        sum += ringDist[i];                               // sum是后缀
        C[i] = max(C[i + 1], dep[ring[i]] + sum);         //子树深度+后缀长度
        D[i] = max(D[i + 1], sum + maxx + dep[ring[i]]);  //用之前最深的+当前子树深度+前缀长度
        maxx = max(maxx, dep[ring[i]] - sum);             //维护最深的子树深度
    }

    long long ans2 = B[ringCnt];

    for (int i = 1; i < ringCnt; i++) ans2 = min(max(max(B[i], D[i + 1]), A[i] + C[i + 1] + tmp), ans2);  //从i拆开的三种情况

    printf("%.1lf\n", (double)max(ans, ans2) / 2.0);
    return 0;
}
