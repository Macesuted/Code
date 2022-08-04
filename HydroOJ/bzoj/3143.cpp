/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar()) x = x * 10 + (c & 15);
    return x * f;
}

class Matrix {
   private:
    vector<vector<double>> matrix;

   public:
    int n, m;
    void resize(int _n, int _m) {
        matrix.resize(n = _n), m = _m;
        for (auto& i : matrix) i.resize(m);
        return;
    }
    vector<double>& operator[](int p) { return matrix[p]; }
    double get(int i, int j) const { return matrix[i][j]; }
    Matrix operator*(const Matrix& b) {
        Matrix a = *this, ans;
        assert(a.m == b.n);
        ans.resize(a.n, b.m);
        for (int i = 0; i < a.n; i++)
            for (int j = 0; j < a.m; j++)
                for (int k = 0; k < b.m; k++) ans[i][k] += a.get(i, j) * b.get(j, k);
        return ans;
    }
    Matrix getRev(void) {
        Matrix a = *this, b;
        assert(a.n == a.m);
        int n = a.n;
        b.resize(n, n);
        for (int i = 0; i < n; i++) b[i][i] = 1;
        for (int i = 0; i < n; i++) {
            int p = i;
            for (int j = i + 1; j < n; j++)
                if (a[j][i] > a[p][i]) p = j;
            for (int j = 0; j < n; j++) swap(a[i][j], a[p][j]), swap(b[i][j], b[p][j]);
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                double mul = a[j][i] / a[i][i];
                for (int k = 0; k < n; k++) a[j][k] -= a[i][k] * mul, b[j][k] -= b[i][k] * mul;
            }
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) b[i][j] /= a[i][i];
        return b;
    }
};

#define maxn 505

int deg[maxn];
double invDeg[maxn];

vector<vector<int>> graph;
vector<double> f;

int main() {
    ios::sync_with_stdio(false);
    int n = read<int>(), m = read<int>();
    graph.resize(n);
    for (int i = 1; i <= m; i++) {
        int x = read<int>() - 1, y = read<int>() - 1;
        graph[x].push_back(y), graph[y].push_back(x);
        deg[x]++, deg[y]++;
    }
    for (int i = 0; i < n; i++) invDeg[i] = 1. / deg[i];
    Matrix M;
    M.resize(n - 1, n - 1);
    for (int i = 0; i < n - 1; i++) {
        M[i][i] = 1;
        for (auto j : graph[i])
            if (j < n - 1) M[i][j] = -invDeg[j];
    }
    M = M.getRev();
    Matrix A;
    A.resize(n - 1, 1), A[0][0] = 1;
    Matrix F = M * A;
    for (int i = 0; i < n; i++)
        for (auto j : graph[i]) {
            if (j < i) continue;
            f.push_back((i == n - 1 ? 0 : F[i][0]) * invDeg[i] + (j == n - 1 ? 0 : F[j][0]) * invDeg[j]);
        }
    sort(f.begin(), f.end());
    double answer = 0;
    for (int i = 0; i < m; i++) answer += f[i] * (m - i);
    cout << setiosflags(ios::fixed) << setprecision(3) << answer << endl;
    return 0;
}