/**
 * @file 11360.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define MP make_pair
#define MT make_tuple

#ifdef MACESUTED

bool mem1;

#endif

#define maxn 155

typedef tuple<int, int, int> tiii;

class SlimeXSlimeRancher {
   private:
    short cnt[maxn][maxn][maxn];
    long long f[maxn][maxn][maxn], A[maxn], B[maxn], C[maxn];
    tiii a[maxn];

   public:
    long long train(vector<string> first_slime, vector<string> second_slime, vector<string> third_slime) {
        string sa, sb, sc;
        for (auto &i : first_slime) sa += i;
        for (auto &i : second_slime) sb += i;
        for (auto &i : third_slime) sc += i;
        stringstream sina(sa), sinb(sb), sinc(sc);
        int n = 0;
        tiii cache;
        while (sina >> get<0>(cache)) sinb >> get<1>(cache), sinc >> get<2>(cache), a[++n] = cache;
        long long sum = 0;
        for (int i = 1; i <= n; i++) A[i] = get<0>(a[i]), B[i] = get<1>(a[i]), C[i] = get<2>(a[i]), sum += A[i] + B[i] + C[i];
        sort(A + 1, A + n + 1), sort(B + 1, B + n + 1), sort(C + 1, C + n + 1);
        for (int i = 1; i <= n; i++)
            get<0>(a[i]) = lower_bound(A + 1, A + n + 1, get<0>(a[i])) - A,
            get<1>(a[i]) = lower_bound(B + 1, B + n + 1, get<1>(a[i])) - B,
            get<2>(a[i]) = lower_bound(C + 1, C + n + 1, get<2>(a[i])) - C;
        for (int i = 1; i <= n; i++) cnt[get<0>(a[i])][get<1>(a[i])][get<2>(a[i])]++;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++) cnt[i][j][k] += cnt[i - 1][j][k];
        for (int j = 2; j <= n; j++)
            for (int i = 1; i <= n; i++)
                for (int k = 1; k <= n; k++) cnt[i][j][k] += cnt[i][j - 1][k];
        for (int k = 2; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++) cnt[i][j][k] += cnt[i][j][k - 1];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++) {
                    long long c = A[i] + B[j] + C[k];
                    f[i][j][k] = min({f[i - 1][j][k] + c * (cnt[i][j][k] - cnt[i - 1][j][k]),
                                      f[i][j - 1][k] + c * (cnt[i][j][k] - cnt[i][j - 1][k]),
                                      f[i][j][k - 1] + c * (cnt[i][j][k] - cnt[i][j][k - 1])});
                }
        return f[n][n][n] - sum;
    }
};

#ifdef MACESUTED

SlimeXSlimeRancher _;

bool mem2;

int main() {
    ios::sync_with_stdio(false);
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    string a, b, c;
    int n;
    cin >> n;
    getline(cin, a);
    getline(cin, a), getline(cin, b), getline(cin, c);
    vector<string> A, B, C;
    A.push_back(a), B.push_back(b), C.push_back(c);
    cout << _.train(A, B, C) << endl;

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}

#endif