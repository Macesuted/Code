/**
 * @file TC2025C1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-17
 *
 * @copyright Copyright (c) 2025
 * @brief 903257 pts with 38% hit
 *
 */

#include <bits/stdc++.h>
using namespace std;

const double ALPHA_X = 8.0;
const double ALPHA_Y = 8.0;
const double BETA_X = 1.0;
const double BETA_Y = 1.0;

inline double sqr(const double &x) { return x * x; }

struct Point {
    double X, Y;
};

class Vehicle {
   private:
   public:
    int type;
    Point nodes[4], center, size;
    double vx, vy;
    double dx, dy;

    double calcDeltaX(const Vehicle &o) const {
        return BETA_X * (abs(this->center.X - o.center.X) - (this->size.X + o.size.X) / 2) /
               (ALPHA_X * abs(this->vx - o.vx) + 1);
    }
    double calcDeltaY(const Vehicle &o) const {
        return BETA_Y * (abs(this->center.Y - o.center.Y) - (this->size.Y + o.size.Y) / 2) /
               (ALPHA_Y * abs(this->vy - o.vy) + 1);
    }
    double calcDelta(const Vehicle &o) const {
        // if (o.center.X < this->center.X || o.vx > this->vx) return 1e18;
        double vx = calcDeltaX(o), vy = calcDeltaY(o);
        if (vx < 0 || vy < 0) return 1e18;
        return sqrt(sqr(vx) + sqr(vy));
        // return min(vx, vy);
    }

   public:
    void input(bool inputType = true, bool inputY = true, bool inputA = true) {
        type = 0;
        if (inputType) cin >> type;

        for (int t = 0; t < 4; t++) cin >> nodes[t].X >> nodes[t].Y;

        center.X = center.Y = 0;
        for (int t = 0; t < 4; t++) center.X += nodes[t].X, center.Y += nodes[t].Y;
        center.X /= 4, center.Y /= 4;

        double maxX = nodes[0].X, minX = nodes[0].X, maxY = nodes[0].Y, minY = nodes[0].Y;
        for (int t = 0; t < 4; t++) {
            maxX = max(maxX, nodes[t].X), minX = min(minX, nodes[t].X);
            maxY = max(maxY, nodes[t].Y), minY = min(minY, nodes[t].Y);
        }
        size.X = maxX - minX, size.Y = maxY - minY;

        cin >> vx;
        vy = 0;
        if (inputY) cin >> vy;

        dx = dy = 0;
        if (inputA) cin >> dx >> dy;

        return;
    }
    void move(double K) {
        center.X += K * vx + dx / 2 * K * K;
        center.Y += K * vy + dy / 2 * K * K;
        vx += dx * K;
        vy += dy * K;
        return;
    }

    double calcRisk(const Vehicle &o) const { return 1 / (this->calcDelta(o) + 1); }
};

const double K = 0.2;
const double SAFE_LIM = 0.715;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int M;
    cin >> M;

    double oa = 0;

    for (int test = 1; test <= M; test++) {
        Vehicle Ego;
        Ego.input(false, false, false);

        double ov = sqrt(Ego.vx * Ego.vx + Ego.vy * Ego.vy);

        size_t N;
        cin >> N;
        vector<Vehicle> Objs(N);
        for (size_t i = 0; i < N; i++) Objs[i].input(true, true, true), Objs[i].move(K);

        double ans = 0;

        vector<pair<double, double>> avaiV;

        for (double v = 36; v >= 0; v -= 0.1) {
            double a = min(max((v - ov) / K, max(oa - 4 * K, -6.)), min(oa + K, 2.));
            if (test == 1) a = min(max((v - ov) / K, -6.), 2.);

            Vehicle newEgo = Ego;
            newEgo.dx = a, newEgo.move(max(a, 1.) * K);
            bool safe = true;
            for (size_t i = 0; i < N && safe; i++)
                if (newEgo.calcRisk(Objs[i]) > SAFE_LIM) safe = false;

            if (safe) avaiV.emplace_back(v, a);
        }

        sort(avaiV.begin(), avaiV.end());
        if (!avaiV.empty()) {
            // tie(ans, oa) = avaiV[max((size_t)0, avaiV.size() - 1 - rnd() % 5)];
            // tie(ans, oa) = avaiV.back();
            for (auto [v, a] : avaiV)
                if (abs(v - ov) < abs(ans - ov)) tie(ans, oa) = {v, a};
        }

        cout << ans << endl;
    }

    return 0;
}