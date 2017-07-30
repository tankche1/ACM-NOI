// UVa11292 The Dragon of Loowater
// Rujia Liu
#include<cstdio>
#include<algorithm>       // ��Ϊ�õ���sort
using namespace std;

const int maxn = 20000 + 5;
int A[maxn], B[maxn];
int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2 && n && m) {
    for(int i = 0; i < n; i++) scanf("%d", &A[i]);
    for(int i = 0; i < m; i++) scanf("%d", &B[i]);
    sort(A, A+n);
    sort(B, B+m);
    int cur = 0;         // ��ǰ��Ҫ������ͷ�ı��
    int cost = 0;        // ��ǰ�ܷ���
    for(int i = 0; i < m; i++)
      if(B[i] >= A[cur]) {
        cost += B[i];           // ��Ӷ����ʿ
        if(++cur == n) break;   // ���ͷ�Ѿ����꣬��ʱ�˳�ѭ��
      }
    if(cur < n) printf("Loowater is doomed!\n");
    else printf("%d\n", cost);
  }
  return 0;
}
