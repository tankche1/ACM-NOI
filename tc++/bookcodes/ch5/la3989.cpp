// LA3989 Ladies' Choice
// Rujia Liu
#include<cstdio>
#include<queue>
using namespace std;

const int maxn = 1000 + 10;
int pref[maxn][maxn], order[maxn][maxn], next[maxn], future_husband[maxn], future_wife[maxn];
queue<int> q; // δ�������ʿ����

void engage(int man, int woman) {
  int m = future_husband[woman];
  if(m) {
    future_wife[m] = 0; // ��������δ�������еĻ���
    q.push(m); // ����δ������ʿ����
  }
  future_wife[man] = woman;
  future_husband[woman] = man;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int n;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++)
        scanf("%d", &pref[i][j]); // ���Ϊi����ʿ��jϲ������
      next[i] = 1; // ������Ӧ������Ϊ1��Ůʿ���
      future_wife[i] = 0; // û��δ����
      q.push(i);
    }

    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        int x;
        scanf("%d", &x);
        order[i][x] = j; // �ڱ��Ϊi��Ůʿ��Ŀ�У����Ϊx����ʿ������
      }
      future_husband[i] = 0; // û��δ���
    }

    while(!q.empty()) {
      int man = q.front(); q.pop();
      int woman = pref[man][next[man]++];
      if(!future_husband[woman]) engage(man, woman); // womanû��δ���ֱ�Ӷ���
      else if(order[woman][man] < order[woman][future_husband[woman]]) engage(man, woman); // ��δ���
      else q.push(man); // �´�����
    }
    while(!q.empty()) q.pop();

    for(int i = 1; i <= n; i++) printf("%d\n", future_wife[i]);
    if(T) printf("\n");
  }
  return 0;
}
