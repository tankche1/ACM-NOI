// LA3485 Bridge: ����Ӧ����ɭ��
// Rujia Liu
#include<cstdio>
#include<cmath>

// ����Ϊ�˷��㣬��a������ȫ�ֵġ�
// �ⲻ��һ���õı��ϰ�ߣ����ڱ�����ȴ������ߴ���Ŀɶ���
double a; 

// simpson��ʽ�õ��ĺ���
double F(double x) {
  return sqrt(1 + 4*a*a*x*x);
}

// ����simpson��������Ҫ��F��һ��ȫ�ֺ���
double simpson(double a, double b) {
  double c = a + (b-a)/2;
  return (F(a)+4*F(c)+F(b))*(b-a)/6;
}

// ����ӦSimpson��ʽ���ݹ���̣�����֪��������[a,b]�ϵ�����simpsonֵA
double asr(double a, double b, double eps, double A) {
  double c = a + (b-a)/2;
  double L = simpson(a, c), R = simpson(c, b);
  if(fabs(L+R-A) <= 15*eps) return L+R+(L+R-A)/15.0;
  return asr(a, c, eps/2, L) + asr(c, b, eps/2, R);
}

// ����ӦSimpson��ʽ�������̣�
double asr(double a, double b, double eps) {
  return asr(a, b, eps, simpson(a, b));
}

// ������ӦSimpson��ʽ������Ϊw���߶�Ϊh�������߳�
double parabola_arc_length(double w, double h) {
  a = 4.0*h/(w*w); // �޸�ȫ�ֱ���a���Ӷ��ı�ȫ�ֺ���F����Ϊ
  return asr(0, w/2, 1e-5)*2;
}

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    int D, H, B, L;
    scanf("%d%d%d%d", &D, &H, &B, &L);
    int n = (B+D-1)/D; // �����
    double D1 = (double)B / n;
    double L1 = (double)L / n;
    double x = 0, y = H;
    while(y-x > 1e-5) { // ���ַ����߶�
      double m = x + (y-x)/2;
      if(parabola_arc_length(D1, m) < L1) x = m; else y = m;
    }
    if(kase > 1) printf("\n");
    printf("Case %d:\n%.2lf\n", kase, H-x);
  }
  return 0;
}