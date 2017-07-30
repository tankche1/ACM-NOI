// LA3644 X-Plosives
// Rujia Liu
#include <cstdio>
const int maxn = 100000 + 10;
int pa[maxn];

// ���鼯�Ĳ��Ҳ�������·��ѹ��
int findset(int x) { return pa[x] != x ? pa[x] = findset(pa[x]) : x; } 

int main() {
  int x, y;
  while(scanf("%d", &x) == 1) {
    for(int i = 0; i <= maxn; i++) pa[i] = i;
    int refusals = 0;
    while(x != -1) {
      scanf("%d", &y);
      x = findset(x); y = findset(y);
      if(x == y) ++refusals; // ���x��y��ͬһ�����ϣ���ܾ�
      else pa[x] = y; // ����ϲ�������û��ʹ������ʽ�ϲ�
      scanf("%d", &x);
    }
    printf("%d\n", refusals);
  }
  return 0;
}
