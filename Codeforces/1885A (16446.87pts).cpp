/**
 * @file 1885A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-11-28
 *
 * @copyright Copyright (c) 2023
 * qwq
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

struct Ques {
    int id, Tbegin, Tend, n;
    double TBS, SINR;
};

int N, K, T, R, J;
vector<vector<vector<vector<double>>>> S0, d, P, nP;
double tmp[1000][10], oldP[10][100];
int mod[1000][10], usePos[1000][10], quesId[1000][100];
set<int> user[1000][10][10], finish;
Ques ques[5000];
bool done[5000];

inline bool B(int t, int k, int r, int n) { return P[t][k][r][n] > 0; }

double sumP(int t, int k, int r) {
    double sum = 0;
    for (int n = 0; n < N; n++) sum += P[t][k][r][n];
    return sum;
}

double sumP(int t, int k) {
    double sum = 0;
    for (int r = 0; r < R; r++) sum += sumP(t, k, r);
    return sum;
}

int cntRestR(int t) {
    int cnt = 0;
    for (int r = 0; r < R; r++) cnt += !mod[t][r];
    return cnt;
}

double maxP(int t, int k) { return min(4., R - sumP(t, k)); }
double avgP(int t, int k) { return min(4., (R - sumP(t, k)) / cntRestR(t)); }

double SINR(int t, int k, int r, int n) {
    double up = S0[t][k][r][n] * P[t][k][r][n], down = 1;
    for (auto m : user[t][k][r])
        if (m != n) up *= exp(d[k][r][m][n]);
    for (int k_ = 0; k_ < K; k_++)
        if (k_ != k)
            for (auto n_ : user[t][k_][r])
                if (n_ != n) down += S0[t][k_][r][n] * P[t][k_][r][n_] * exp(-d[k_][r][n][n_]);
    return up / down;
}

double SINR(int t, int k, int n) {
    double total = 1;
    int cnt = 0;
    for (int r = 0; r < R; r++)
        if (B(t, k, r, n)) total *= SINR(t, k, r, n), cnt++;
    return pow(total, 1. / cnt);
}

double G(int t, int n) {
    double total = 0;
    for (int k = 0; k < K; k++) {
        int cnt = 0;
        for (int r = 0; r < R; r++) cnt += B(t, k, r, n);
        if (cnt) total += cnt * log2(1 + SINR(t, k, n));
    }
    return total * 192;
}

double G(Ques q) {
    double total = 0;
    for (int t = q.Tbegin; t <= q.Tend; t++) total += G(t, q.n);
    return total;
}

double tryMaxG(int t, int r, int n, double lim = 4) {
    for (int k = 0; k < K; k++) P[t][k][r][n] = min(lim, maxP(t, k)), user[t][k][r].insert(n);
    double val = G(t, n);
    for (int k = 0; k < K; k++) P[t][k][r][n] = 0, user[t][k][r].erase(n);
    return val;
}
double tryPercentG(int t, int r, int n, double percent = 1) {
    for (int k = 0; k < K; k++) P[t][k][r][n] = maxP(t, k) * percent, user[t][k][r].insert(n);
    double val = G(t, n);
    for (int k = 0; k < K; k++) P[t][k][r][n] = 0, user[t][k][r].erase(n);
    return val;
}

double calc(int t, int k, int r, int n) {
    double prodD = 1;
    for (auto m : user[t][k][r])
        if (m != n) prodD *= exp(d[k][r][m][n]);
    return ques[quesId[t][n]].SINR / S0[t][k][r][n] / prodD + 1e-6;
};

bool adapt(int t, int r) {
    int k = usePos[t][r];
    double lim = min(4., R - (sumP(t, k) - sumP(t, k, r)));
    for (auto n : user[t][k][r]) {
        P[t][k][r][n] = calc(t, k, r, n);
        if ((lim -= P[t][k][r][n]) < 0) return false;
    }
    return true;
};

int main() {
#ifdef LOCAL
    // freopen("E:\\Code\\_work\\00", "r", stdin);
    // freopen("E:\\Code\\_work\\06", "r", stdin);
    freopen("E:\\Code\\_work\\21", "r", stdin);
    // freopen("E:\\Code\\_work\\3X", "r", stdin);
    // freopen("E:\\Code\\_work\\51", "r", stdin);
    freopen("E:\\Code\\_work\\out", "w", stdout);
    freopen("E:\\Code\\_work\\log", "w", stderr);
#endif

    mt19937 rnd(20080618);
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> N >> K >> T >> R;
    cout << setprecision(8) << setiosflags(ios::fixed);
    cerr << setprecision(8) << setiosflags(ios::fixed);

    S0.resize(T), P.resize(T), nP.resize(T);
    for (int t = 0; t < T; t++) {
        S0[t].resize(K), P[t].resize(K), nP[t].resize(K);
        for (int k = 0; k < K; k++) {
            S0[t][k].resize(R), P[t][k].resize(R), nP[t][k].resize(R);
            for (int r = 0; r < R; r++) {
                S0[t][k][r].resize(N), P[t][k][r].resize(N), nP[t][k][r].resize(N);
                for (int n = 0; n < N; n++) cin >> S0[t][k][r][n];
            }
        }
    }
    d.resize(K);
    for (int k = 0; k < K; k++) {
        d[k].resize(R);
        for (int r = 0; r < R; r++) {
            d[k][r].resize(N);
            for (int m = 0; m < N; m++) {
                d[k][r][m].resize(N);
                for (int n = 0; n < N; n++) cin >> d[k][r][m][n];
            }
        }
    }

    for (int t = 0; t < T; t++)
        for (int n = 0; n < N; n++) quesId[t][n] = -1;

    cin >> J;

    for (int i = 0; i < J; i++) {
        cin >> ques[i].id >> ques[i].TBS >> ques[i].n >> ques[i].Tbegin >> ques[i].Tend;
        ques[i].Tend += ques[i].Tbegin - 1, ques[i].SINR = pow(2, ques[i].TBS / 192.) - 1;
        for (int t = ques[i].Tbegin; t <= ques[i].Tend; t++) quesId[t][ques[i].n] = i;
    }

    int expectation = 0, pt = 0;
    {
        set<tuple<double, int, int, int, int>> pos0, pos2;
        vector<set<tuple<double, int, int, int, int>>::iterator> ins0[1000][100], ins2[1000][100];

        auto insert = [&](int i, int t) {
            int n = ques[i].n;
            for (int r = 0; r < R; r++)
                if (!mod[t][r]) {
                    for (int k = 0; k < K; k++)
                        if (ques[i].SINR / S0[t][k][r][n] + 1e-6 <= maxP(t, k)) {
                            bool used = false;
                            for (int r = 0; r < R; r++) used |= (mod[t][r] == 2 && usePos[t][r] == k);
                            if (used) continue;
                            ins0[t][n].push_back(pos0.emplace(ques[i].SINR / S0[t][k][r][n], t, k, r, n).first);
                        }
                } else if (mod[t][r] == 2) {
                    int k = usePos[t][r];
                    double curTotP = sumP(t, k, r);
                    user[t][k][r].insert(n);
                    if (adapt(t, r)) ins2[t][n].push_back(pos2.emplace(sumP(t, k, r) - curTotP, t, k, r, n).first);
                    P[t][k][r][n] = 0, user[t][k][r].erase(n), adapt(t, r);
                }
            return;
        };

        for (int i = 0; i < J; i++)
            if (!done[i])
                for (int t = ques[i].Tbegin; t <= ques[i].Tend; t++) insert(i, t);
        while (true) {
            double value;
            int t, k, r, n, i;
            bool ins = false;
            if (!pos2.empty()) {
                tie(value, t, k, r, n) = *pos2.begin(), i = quesId[t][n];
                user[t][k][r].insert(n), adapt(t, r);
                expectation++, done[i] = true, finish.insert(i);
            } else if (!pos0.empty()) {
                tie(value, t, k, r, n) = *pos0.begin(), i = quesId[t][n];
                mod[t][r] = 2, usePos[t][r] = k;
                user[t][k][r].insert(n), adapt(t, r);
                expectation++, done[i] = true, finish.insert(i);
            } else {
                if (finish.empty() || clock() * 1000. / CLOCKS_PER_SEC > 1700) break;
                while (!done[pt]) pt = (pt + 1) % J;
                i = pt++, n = ques[i].n;
                for (int t_ = ques[i].Tbegin; t_ <= ques[i].Tend; t_++)
                    for (int k_ = 0; k_ < K; k_++)
                        for (int r_ = 0; r_ < R; r_++)
                            if (B(t_, k_, r_, n)) tie(t, k, r) = {t_, k_, r_};
                P[t][k][r][n] = 0, user[t][k][r].erase(n);
                expectation--, done[i] = false, finish.erase(i), ins = true;
                if (user[t][k][r].empty())
                    mod[t][r] = 0;
                else
                    adapt(t, r);
            }
            if (ins) {
                for (int t = ques[i].Tbegin; t <= ques[i].Tend; t++) insert(i, t);
                for (int m = 0; m < N; m++) {
                    if (n == m) continue;
                    int i = quesId[t][m];
                    if (~i && !done[i]) insert(i, t);
                }
            } else {
                for (int t = ques[i].Tbegin; t <= ques[i].Tend; t++) {
                    for (auto i : ins0[t][n]) pos0.erase(i);
                    for (auto i : ins2[t][n]) pos2.erase(i);
                    ins0[t][n].clear(), ins2[t][n].clear();
                }
                for (int n = 0; n < N; n++) {
                    for (auto i : ins0[t][n]) pos0.erase(i);
                    for (auto i : ins2[t][n]) pos2.erase(i);
                    ins0[t][n].clear(), ins2[t][n].clear();
                }

                for (int n = 0; n < N; n++) {
                    int i = quesId[t][n];
                    if (~i && !done[i]) insert(i, t);
                }
            }
        }
    }

    {
        vector<int> ids;
        for (int i = 0; i < J; i++) ids.push_back(i);
        sort(ids.begin(), ids.end(), [&](int x, int y) { return ques[x].TBS < ques[y].TBS; });
        for (auto i : ids) {
            if (done[i]) continue;
            int n = ques[i].n;

            vector<tuple<double, double, int, int, int>> pos0;
            vector<tuple<double, double, double, int, int>> pos2;
            for (int t = ques[i].Tbegin; t <= ques[i].Tend; t++)
                for (int r = 0; r < R; r++)
                    if (mod[t][r] == 0) {
                        for (int k = 0; k < K; k++) {
                            bool used = false;
                            for (int r = 0; r < R; r++) used |= (mod[t][r] == 2 && usePos[t][r] == k);
                            if (used) continue;
                            pos0.emplace_back(S0[t][k][r][n], log2(1 + S0[t][k][r][n] * maxP(t, k)), t, k, r);
                        }
                    } else if (mod[t][r] == 2) {
                        int k = usePos[t][r];
                        double totP = 0, prodD = 1;
                        for (auto m : user[t][k][r]) totP += P[t][k][r][m] / exp(d[k][r][n][m]), prodD *= exp(d[k][r][n][m]);
                        double restP = min(4. - totP, R - sumP(t, k) - (totP - sumP(t, k, r)));
                        if (restP <= 1e-6) continue;
                        pos2.emplace_back(S0[t][k][r][n] * prodD, S0[t][k][r][n] * prodD, restP, t, r);
                    }
            sort(pos0.begin(), pos0.end(), greater<tuple<double, double, int, int, int>>());
            sort(pos2.begin(), pos2.end(), greater<tuple<double, double, double, int, int>>());

            double rest = ques[i].TBS / 192.;
            vector<pair<int, int>> upd;
            for (auto [val, newS0, restP, t, r] : pos2) {
                int k = usePos[t][r];

                for (auto m : user[t][k][r])
                    nP[t][k][r][m] = P[t][k][r][m], P[t][k][r][m] = P[t][k][r][m] / exp(d[k][r][n][m]) + 1e-6;
                P[t][k][r][n] = min({maxP(t, k), 4. - sumP(t, k, r), (pow(2, rest) - 1) / val + 1e-6});
                user[t][k][r].insert(n);
                upd.emplace_back(t, r);
                rest -= log2(1 + newS0 * P[t][k][r][n]);
                if (rest <= 0) break;
            }

            if (rest <= 0) {
                done[i] = true, expectation++, finish.insert(i);
                continue;
            }
            for (auto [t, r] : upd) {
                int k = usePos[t][r];
                P[t][k][r][n] = 0, user[t][k][r].erase(n);
                for (auto m : user[t][k][r]) P[t][k][r][m] = nP[t][k][r][m];
            }
        }
    }

    cerr << expectation << endl;

    {
        vector<int> ids;
        for (int i = 0; i < J; i++) ids.push_back(i);
        sort(ids.begin(), ids.end(), [&](int x, int y) { return ques[x].TBS < ques[y].TBS; });
        for (auto i : ids) {
            if (done[i]) continue;
            int n = ques[i].n;

            set<tuple<double, int, int>> S;
            for (int t = ques[i].Tbegin; t <= ques[i].Tend; t++)
                for (int r = 0; r < R; r++)
                    if (!mod[t][r]) S.emplace(tmp[t][r] = tryMaxG(t, r, n), t, r);

            vector<pair<int, int>> modify;
            double rest = ques[i].TBS;
            while (rest > 0 && !S.empty()) {
                auto p = --S.end();
                auto [value, t, r] = *p;
                S.erase(p);
                modify.emplace_back(t, r);
                double cur = G(t, n);
                if (tryMaxG(t, r, n) - cur > rest) {
                    double pl = 0, pr = 1;
                    while (pl + 1e-6 < pr) {
                        double mid = (pl + pr) / 2;
                        ((tryPercentG(t, r, n, mid) - cur >= rest) ? pr : pl) = mid;
                    }
                    for (int k = 0; k < K; k++) P[t][k][r][n] = maxP(t, k) * pr;
                } else
                    for (int k = 0; k < K; k++) P[t][k][r][n] = avgP(t, k);
                mod[t][r] = 1;
                for (int k = 0; k < K; k++) user[t][k][r].insert(n);
                rest += cur, cur = G(t, n), rest -= cur;
                for (int r_ = 0; r_ < R; r_++)
                    if (!mod[t][r_]) S.erase({tmp[t][r_], t, r_}), S.emplace(tmp[t][r_] = tryMaxG(t, r_, n) - cur, t, r_);
            }
            if (rest <= 0) {
                expectation++, done[i] = true, finish.insert(i);
                continue;
            }
            for (auto [t, r] : modify) {
                mod[t][r] = 0;
                for (int k = 0; k < K; k++) user[t][k][r].clear(), P[t][k][r][n] = 0;
            }
        }
    }

    double score = 0;
    for (int t = 0; t < T; t++)
        for (int k = 0; k < K; k++)
            for (int r = 0; r < R; r++) {
                for (int n = 0; n < N; n++) cout << P[t][k][r][n] << ' ', score -= P[t][k][r][n] * 1e-6;
                cout << endl;
            }

    for (int i = 0; i < J; i++)
        if (G(ques[i]) >= ques[i].TBS) score += 1;
    cerr << "Score = " << score << endl;
    cerr << "Expectation = " << expectation << '/' << J << endl;
#ifdef LOCAL
    for (int t = 0; t < T; t++)
        for (int k = 0; k < K; k++) {
            assert(sumP(t, k) <= R + 1e-6);
            for (int r = 0; r < R; r++) {
                assert(sumP(t, k, r) <= 4 + 1e-6);
                for (int n = 0; n < N; n++) assert(P[t][k][r][n] >= 0);
            }
        }

    cerr << endl;
    for (int t = 0; t < T; t++) {
        cerr << "T = " << t << endl;
        for (int r = 0; r < R; r++) {
            cerr << "R " << r << " MOD " << mod[t][r];
            for (int k = 0; k < K; k++) {
                cerr << " (" << k << ',' << sumP(t, k, r) << ')';
                for (auto n : user[t][k][r]) cerr << n << ',';
            }
            cerr << endl;
        }
        cerr << endl;
        for (int k = 0; k < K; k++) {
            cerr << "K " << k << " SUM " << sumP(t, k) << " MAX ";
            double maxP = 0;
            for (int r = 0; r < R; r++) maxP = max(maxP, sumP(t, k, r));
            cerr << maxP << endl;
            for (int n = 0; n < N; n++) cerr << SINR(t, k, n) << ' ';
            cerr << endl;
        }
    }
#endif

    return 0;
}