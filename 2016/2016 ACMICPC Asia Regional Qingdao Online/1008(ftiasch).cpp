#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1 << 21;

struct Complex
{
    Complex(double x = 0., double y = 0.) : x(x), y(y) {}

    double x, y;
};

Complex operator + (const Complex& a, const Complex& b)
{
    return Complex(a.x + b.x, a.y + b.y);
}

Complex operator - (const Complex& a, const Complex& b)
{
    return Complex(a.x - b.x, a.y - b.y);
}

Complex operator * (const Complex& a, const Complex& b)
{
    return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

Complex a[N], b[N];

const double pi = acos(-1.);

void sincos(double p, double& y, double& x)
{
    y = sin(p);
    x = cos(p);
}

void FFT(Complex P[], int n, int oper)
{
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            std::swap(P[i], P[j]);
        }
    }
    Complex unit_p0;
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2;
        double p0 = pi / m * oper;
        sincos(p0, unit_p0.y, unit_p0.x);
        for (int i = 0; i < n; i += m2) {
            Complex unit = 1;
            for (int j = 0; j < m; j++) {
                Complex &P1 = P[i + j + m], &P2 = P[i + j];
                Complex t = unit * P1;
                P1 = P2 - t;
                P2 = P2 + t;
                unit = unit * unit_p0;
            }
        }
    }
}


int main()
{
#ifdef LOCAL_JUDGE
    freopen("H.in", "r", stdin);
#endif
    int n, m;
    double R;
    while (scanf("%d%d%lf", &n, &m, &R) == 3) {
        int r = 0;
        while (r + 1 <= R) {
            r ++;
        }
        int N = r + n + r;
        int M = r + m + r;
        int K = 0;
        while (1 << K < N * M) {
            K ++;
        }
        memset(a, 0, sizeof(*a) << K);
        memset(b, 0, sizeof(*b) << K);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                double x;
                scanf("%lf", &x);
                a[i * M + j] = x;
            }
        }
        FFT(a, 1 << K, 1);
        for (int i = -r; i <= r; ++ i) {
            for (int j = -r; j <= r; ++ j) {
                double s = std::hypot(i, j);
                if (s < R) {
                    b[(i + r) * M + (j + r)] = 1 / (1 + s);
                }
            }
        }
        FFT(b, 1 << K, 1);
        for (int i = 0; i < 1 << K; ++ i) {
            a[i] = a[i] * b[i];
        }
        FFT(a, 1 << K, -1);
        double result = 0.;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                double ref = (a[(i + r) * M + (j + r)].x) / (1 << K);
                result = std::max(result,  ref);
            }
        }
        printf("%.3f\n", result);
    }
}
