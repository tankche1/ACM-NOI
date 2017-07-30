// UVa10881 Piotr's Ants
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;

struct Ant {
  int id; // ����˳��
  int p;  // λ��
  int d;  // ���� -1: ��; 0:ת����; 1:��
  bool operator < (const Ant& a) const {
    return p < a.p;
  }
} before[maxn], after[maxn];

const char dirName[][10] = {"L", "Turning", "R"};

int order[maxn]; // ����ĵ�iֻ��������̬�е�������order[i]ֻ����

int main() {
  int K;
  scanf("%d", &K);
  for(int kase = 1; kase <= K; kase++) {
    int L, T, n;
    printf("Case #%d:\n", kase);
    scanf("%d%d%d", &L, &T, &n);
    for(int i = 0; i < n; i++) {
      int p, d;
      char c;
      scanf("%d %c", &p, &c);
      d = (c == 'L' ? -1 : 1);
      before[i] = (Ant){i, p, d};
      after[i] = (Ant){0, p+T*d, d}; // �����id��δ֪��
    }

    // ����order����
    sort(before, before+n);
    for(int i = 0; i < n; i++)
      order[before[i].id] = i;

    // ������̬
    sort(after, after+n);    
    for(int i = 0; i < n-1; i++) // �޸���ײ�е����ϵķ���
      if(after[i].p == after[i+1].p) after[i].d = after[i+1].d = 0;

    // ������
    for(int i = 0; i < n; i++) {
      int a = order[i]; 
      if(after[a].p < 0 || after[a].p > L) printf("Fell off\n");
      else printf("%d %s\n", after[a].p, dirName[after[a].d+1]);
    }
    printf("\n");
  }
  return 0;
}
