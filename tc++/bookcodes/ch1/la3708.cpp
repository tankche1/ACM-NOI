// LA3708 Graveyard
// Rujia Liu
#include<cstdio>
#include<cmath>
using namespace std;

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    double ans = 0.0;
    for(int i = 1; i < n; i++) {
      double pos = (double)i / n * (n+m); //����ÿ����Ҫ�ƶ��ĵ��ܵ�����
      ans += fabs(pos - floor(pos+0.5)) / (n+m); //�ۼ��ƶ�����
    }
    printf("%.4lf\n", ans*10000); //�ȱ�����������
  }
  return 0;
}
