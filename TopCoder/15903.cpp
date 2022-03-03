/**
 * @file 15903.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-03-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifdef MACESUTED

bool mem1;

#endif

#define maxn 105
#define maxlgm 30

class EllysNim {
   private:
    int A[maxn], B[maxn], n;
    bool ban[maxn];

    bool getXor(int p) {
        bool cnt = 0;
        for (int i = 1; i <= n; i++) cnt ^= (B[i] >> p & 1);
        return cnt;
    }
    pair<int, int> getMaxPos(int p) {
        int maxS = (1 << p) - 1, maxv = -1, maxp = -1;
        for (int i = 1; i <= n; i++)
            if (!ban[i] && !(B[i] >> p & 1) && (B[i] & maxS) > maxv) maxv = (B[maxp = i] & maxS);
        return {maxv, maxp};
    }

   public:
    long long getMin(vector<int> At) {
        int sum = n = 0;
        for (auto i : At) sum ^= (A[++n] = i);
        if (!sum) return 0;
        long long ans = numeric_limits<long long>::max();
        for (int i = maxlgm; ~i; i--) {
            for (int j = 1; j <= n; j++) B[j] = A[j], ban[j] = false;
            bool cnt = getXor(i);
            int maxv, maxp;
            tie(maxv, maxp) = getMaxPos(i);
            if (maxp == -1 && cnt) break;
            if (maxp == -1) continue;
            long long answer = 0;
            ban[maxp] = true, B[maxp] += (1 << i) - maxv, answer += (1 << i) - maxv;
            if (!cnt) {
                int maxv, maxp;
                tie(maxv, maxp) = getMaxPos(i);
                if (maxp == -1) continue;
                ban[maxp] = true, B[maxp] += (1 << i) - maxv, answer += (1 << i) - maxv;
            }
            for (int j = i; ~j; j--) {
                if (!getXor(j)) continue;
                int maxv, maxp;
                tie(maxv, maxp) = getMaxPos(j);
                if (maxp == -1) {
                    answer += 1 << j;
                    continue;
                }
                ban[maxp] = true, B[maxp] += (1 << j) - maxv, answer += (1 << j) - maxv;
            }
            ans = min(ans, answer);
            if (cnt) break;
        }
        return ans;
    }
};

#ifdef MACESUTED

EllysNim _;

bool mem2;

int main() {
    ios::sync_with_stdio(false);
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;

    int n;
    cin >> n;
    vector<int> A;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        A.push_back(t);
    }
    cout << _.getMin(A) << endl;

    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}

#endif