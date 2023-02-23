/**
 * @file 547.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-02-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "guess.h"
#include <bits/stdc++.h>
using namespace std;

#define maxn 3005

int f[maxn];
string X;

string init(string s, int p) {
    for (int i = p; i < (int)s.size(); i++) s[i] = '1';
    return s;
}
void solve(int p, int b, vector<int> S) {
    if (p == b) return;
    int q = p;
    for (auto i : S) {
        while (q > p && query(i, init(X, q))) X[--q] = '0';
        if (q == b) q--;
        X[q] = '0' + query(i, init(X, q + 1)), f[q++] = i;
    }
    for (int i = q - 1; i >= p; i--)
        if (query(f[i], init(X, q)))
            while (q > i + 1) X[--q] = '0';
    S.clear();
    for (int i = p; i < q; i++) S.push_back(f[i]);
    return solve(q, b, S);
}
void solve(int n, int b, int Q) {
    X = string(b, '0');
    vector<int> S;
    for (int i = 1; i <= n; i++) S.push_back(i);
    solve(0, b, S);
    return report(f[b - 1], X);
}