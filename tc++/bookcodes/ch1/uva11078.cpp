// UVa11078 Open Credit System
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;
int A[100000], n;
int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &A[i]);
    int ans = A[0]-A[1];
    int MaxAi = A[0]; // MaxAi��̬ά��A[0]��A[1]������A[j-1]�����ֵ
    for(int j = 1; j < n; j++) { // j��1������0��ʼö�٣���Ϊj=0ʱ��������i
      ans = max(ans, MaxAi-A[j]);
      MaxAi = max(A[j], MaxAi); //MaxAi����ans���¡���һ�룬Ϊʲô
    }
    printf("%d\n", ans);
  }
  return 0;
}
