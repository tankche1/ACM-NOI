// UVa11722 Joining with Friend ������ƪ���������޴˴��룩
// Rujia Liu
#include<cstdio>
double t1, t2, s1, s2, width, height;

// ��ֱ��y=x+w�Ϸ�������(s1,t1)-(s2,t2)�и�õ������
double get_area(double w) {
  double ly = t1+w, ry = t2+w; // ���ҽ����y����
  double tx = s2-w, bx = s1-w; // ���½����x����
  bool on_left   = s1 <= ly && ly <= s2;
  bool on_right  = s1 <= ry && ry <= s2;
  bool on_top    = t1 <= tx && tx <= t2;
  bool on_bottom = t1 <= bx && bx <= t2;
  if(on_left && on_right)   return (s2 - ly + s2 - ry) * width * 0.5;
  if(on_left && on_top)     return (s2 - ly) * (tx - t1) * 0.5;
  if(on_top && on_bottom)   return (bx - t1 + tx - t1) * height * 0.5;
  if(on_right && on_bottom) return height * width - (t2 - bx) * (ry - s1) * 0.5;
  return ly <= s1 ? width * height : 0;
}

int main() {
  int T, kase = 1;
  scanf("%d", &T);
  while(T--) {
    double w;
    scanf("%lf%lf%lf%lf%lf", &t1, &t2, &s1, &s2, &w);
    width = t2 - t1;
    height = s2 - s1;
    double a1 = get_area(w);
    double a2 = get_area(-w);
    printf("Case #%d: %.6lf\n", kase++, (a2 - a1) / width / height);
  }
  return 0;
}
