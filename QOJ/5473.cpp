/**
 * @file 5473.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using pii = pair<int, int>;

void solve(const vector<pii> &A, const vector<pii> &B, int sA, int sB) {
    vector<pii> xA, xB;

    for (size_t i = 0; i < A.size(); i++) xA.emplace_back(A[i].first - A[sA].first, A[i].second - A[sA].second);
    for (size_t i = 0; i < B.size(); i++) xB.emplace_back(B[i].first - B[sB].first, B[i].second - B[sB].second);

    vector<pii> oA, oB;
    if (sA) oA.push_back(xA[0]);
    if (sB) oB.push_back(xB[0]);

    size_t i = sA, j = sB;
    while (i != A.size() && j != B.size())
        if (xA[i] == xB[j])
            i++, j++;
        else if (xA[i] < xB[j])
            oA.push_back(xA[i++]);
        else
            oB.push_back(xB[j++]);
    while (i != A.size()) oA.push_back(xA[i++]);
    while (j != B.size()) oB.push_back(xB[j++]);

    assert(oA.size() == oB.size());

    if (oA.size() == 0) {
        cout << xA[0].first + A[sA].first << ' ' << xA[0].second + A[sA].second << endl;
        cout << xB[0].first + A[sA].first << ' ' << xB[0].second + A[sA].second << endl;
        exit(0);
    }
    if (oA.size() == 1) {
        cout << oA[0].first + A[sA].first << ' ' << oA[0].second + A[sA].second << endl;
        cout << oB[0].first + A[sA].first << ' ' << oB[0].second + A[sA].second << endl;
        exit(0);
    }
    return;
}

void solve(vector<pii> &A, vector<pii> &B) {
    solve(A, B, 0, 0);
    solve(A, B, 0, 1);
    solve(A, B, 1, 0);
    solve(A, B, 1, 1);
    return;
}

void solve(void) {
    auto read = [&](int nA, int mA) -> vector<pii> {
        vector<pii> ret;
        for (int i = 0; i < mA; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < nA; j++)
                if (s[j] == 'o') ret.emplace_back(j, i);
        }
        sort(ret.begin(), ret.end());
        return ret;
    };

    int nA, mA;
    cin >> mA >> nA;
    vector<pii> A = read(nA, mA);
    int nB, mB;
    cin >> mB >> nB;
    vector<pii> B = read(nB, mB);

    auto rotate = [&](vector<pii> &a, int n, int m) -> void {
        for (auto &[x, y] : a) tie(x, y) = make_pair(m + 1 - y, x);
        sort(a.begin(), a.end());
        return;
    };

    solve(A, B);
    rotate(B, nB, mB), swap(nB, mB);
    solve(A, B);
    rotate(B, nB, mB), swap(nB, mB);
    solve(A, B);
    rotate(B, nB, mB), swap(nB, mB);
    solve(A, B);

    return;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int _ = 1;
    while (_--) solve();

    return 0;
}
