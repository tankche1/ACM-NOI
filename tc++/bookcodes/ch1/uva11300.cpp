// UVa11300 Spreading The Wealth
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 10;
long long A[maxn], C[maxn], tot, M;
int main() {
  int n;
  while(scanf("%d", &n) == 1) { // �������ݴ�scanf��cin�� 
    tot = 0;
    for(int i = 1; i <= n; i++) { scanf("%lld", &A[i]); tot += A[i]; } // ��%lld����long long
    M = tot / n;
    C[0] = 0; 
    for(int i = 1; i < n; i++) C[i] = C[i-1] + A[i] - M; // ����C����
    sort(C, C+n);
    long long x1 = C[n/2], ans = 0; // ����x1
    for(int i = 0; i < n; i++) ans += abs(x1 - C[i]); 
    // ��x1���룬����ת�ֵ��ܽ����
    printf("%lld\n", ans);
  }
  return 0;
}
