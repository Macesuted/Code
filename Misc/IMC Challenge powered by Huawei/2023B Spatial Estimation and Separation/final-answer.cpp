/**
 * @file final-answer.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-03-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

using Complex = complex<double>;

const int H2N = 17;
const int H1N = 18;
const int H3N = 28;
const double eps = 5e-5;

const int N_Tx = 32, N_data = 300;

template <typename T>
T sqr(T a) {
    return a * a;
}

class Vector {
    friend class Matrix;

   private:
    vector<Complex> vec;

   public:
    Vector(void) = default;
    Vector(size_t n) { vec.resize(n); }

    Complex &operator[](size_t p) { return vec[p]; }
    Vector operator-(const Vector &v) const {
        int n = this->size();
        Vector ans = *this;
        for (int i = 0; i < n; i++) ans.vec[i] -= v.vec[i];
        return ans;
    }
    template <typename T>
    Vector operator*(const T &v) const {
        Vector ans = *this;
        for (auto &i : ans.vec) i *= v;
        return ans;
    }
    template <typename T>
    Vector operator/(const T &v) const {
        Vector ans = *this;
        for (auto &i : ans.vec) i /= v;
        return ans;
    }

    string toStr(void) const {
        stringstream ssout;
        ssout.clear(), ssout << setiosflags(ios::fixed) << setprecision(6);
        for (auto i : vec) ssout << i.real() << ' ' << i.imag() << ' ';
        return ssout.str();
    }

    size_t size(void) const { return vec.size(); }
    void resize(size_t n) { return vec.resize(n), void(); }
    double fNorm(void) const {
        double sum = 0;
        for (auto i : vec) sum += norm(i);
        return sqrt(sum);
    }
    void normalize(void) {
        double v = fNorm();
        *this = *this / v;
        return;
    }
};
class Matrix {
   private:
    vector<Vector> mtx;

   public:
    Matrix(void) = default;
    Matrix(size_t n, size_t m = 0) {
        mtx.resize(n);
        for (auto &i : mtx) i.resize(m);
        return;
    }

    Vector &operator[](size_t p) { return mtx[p]; }
    Matrix operator-(const Matrix &v) const {
        int n = this->size(), m = this->mtx[0].size();
        Matrix ans = *this;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) ans[i][j] -= v.mtx[i].vec[j];
        return ans;
    }
    template <typename T>
    Matrix operator*(const T &v) const {
        Matrix ans = *this;
        for (auto &i : ans.mtx)
            for (auto &j : i.vec) j *= v;
        return ans;
    }
    template <typename T>
    Matrix operator/(const T &v) const {
        Matrix ans = *this;
        for (auto &i : ans.mtx)
            for (auto &j : i.vec) j /= v;
        return ans;
    }

    string str(void) const {
        string str;
        for (auto &i : mtx) str += i.toStr();
        return str;
    }
    void fromStr(const string &Y_str) {
        stringstream Ycin(Y_str);
        double rel, img;
        for (auto &i : mtx)
            for (auto &j : i.vec) Ycin >> rel >> img, j = Complex(rel, img);
        return;
    }

    size_t size(void) const { return mtx.size(); }
    void resize(size_t n, size_t m = 0) {
        mtx.resize(n);
        for (auto &i : mtx) i.resize(m);
    }
    double fNorm(void) const {
        double sum = 0;
        for (auto &i : mtx)
            for (auto j : i.vec) sum += norm(j);
        return sqrt(sum);
    }
    void normalize(void) { return *this = *this / fNorm(), void(); }
    Matrix trans(void) const {
        Matrix ans(mtx[0].size(), mtx.size());
        for (int i = 0; i < (int)mtx.size(); i++)
            for (int j = 0; j < (int)mtx[0].size(); j++) ans[j][i] = mtx[i].vec[j];
        return ans;
    }
    void elim(void) {
        for (int i = 0; i < (int)mtx.size(); i++) mtx[i].normalize();
        unordered_set<int> Sc;
        for (int i = 0; i < (int)mtx[0].size(); i++) Sc.insert(i);
        int rank = 0;
        while (rank < (int)mtx.size() && !Sc.empty()) {
            int x = rank, y = *Sc.begin();
            for (int j = rank; j < (int)mtx.size(); j++)
                for (auto k : Sc)
                    if (abs(mtx[j][k]) > abs(mtx[x][y])) tie(x, y) = {j, k};
            if (abs(mtx[x][y]) < eps) break;
            swap(mtx[rank], mtx[x]);
            mtx[rank] = mtx[rank] / mtx[rank][y];
            for (int j = rank + 1; j < (int)mtx.size(); j++)
                if (j != rank) mtx[j] = mtx[j] - mtx[rank] * mtx[j][y];
            rank++, Sc.erase(y);
        }
        mtx.resize(rank);
        return;
    }
};

class BlackBoxSystem {
   public:
    Matrix interact(Matrix W1, Matrix W2) const {
        W1 = W1.trans(), W2 = W2.trans();
        double v = sqr(W1.fNorm()) * W2.fNorm();
        W1.normalize(), W2.normalize();
        string W1_str = W1.str(), W2_str = W2.str(), Y_str;
        cout << W1_str << endl << W2_str << endl;
        while (Y_str.size() <= 2) getline(cin, Y_str);
        Matrix Y(N_data, N_Tx);
        Y.fromStr(Y_str);
        return Y.trans() * v;
    }
    void finish(Matrix L_est) const {
        for (int i = 0; i < (int)L_est.size(); i++) L_est[i].normalize();
        string L_est_str = L_est.str();
        cout << L_est_str << endl;
        return;
    }
};

int main() {
    cout << setiosflags(ios::fixed) << setprecision(8);

    BlackBoxSystem blackBox;

    {
        string s;
        cin >> s;
    }

    Matrix Yx[N_Tx];
    for (int i = 0; i < N_Tx; i++) {
        Matrix W1(N_Tx, N_Tx), W2(N_Tx, N_Tx);
        W1[i][0] = W2[H2N][0] = 1;
        Yx[i] = blackBox.interact(W1, W2);
    }

    Matrix L(N_Tx, N_data);
    for (int i = 0; i < N_Tx; i++) {
        Matrix W1(N_Tx, N_Tx), W2(N_Tx, N_Tx);
        W1[H1N][0] += 1, W1[i][0] += 1, W2[H2N][0] = 1;
        L[i] = (blackBox.interact(W1, W2)[H3N] - Yx[H1N][H3N] - Yx[i][H3N]) / 2.;
    }
    L = L.trans(), L.elim();

    {
        cout << "END" << endl;
        string s1, s2;
        cin >> s1 >> s2;
    }

    blackBox.finish(L);

    {
        double score;
        cin >> score;
    }

    return 0;
}
