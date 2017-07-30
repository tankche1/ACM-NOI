// LA3177/UVa1335 Beijing Guards
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, r[maxn], left[maxn], right[maxn]; 

// ����p�������Ƿ��㹻��
// left[i]�ǵ�i�����õ��ġ���ߵ����������right����
bool test(int p) {
  int x = r[1], y = p - r[1];
  left[1] = x; right[1] = 0;
  for(int i = 2; i <= n; i++) {
    if(i % 2 == 1) {
      right[i] = min(y - right[i-1], r[i]); // �������ұߵ�����
      left[i] = r[i] - right[i];
    }
    else {
      left[i] = min(x - left[i-1], r[i]); // ��������ߵ�����
      right[i] = r[i] - left[i];
    }
  }
  return left[n] == 0;
}

int main() {
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 1; i <= n; i++) scanf("%d", &r[i]);
    if(n == 1) { printf("%d\n", r[1]); continue; } // ����n=1
    r[n+1] = r[1];

    int L = 0, R = 0;
    for(int i = 1; i <= n; i++) L = max(L, r[i] + r[i+1]);
    if(n % 2 == 1) {
      for(int i = 1; i <= n; i++) R = max(R, r[i]*3);
      while(L < R) {
        int M = L + (R-L)/2;
        if(test(M)) R = M; else L = M+1;
      }
    }
    printf("%d\n", L);
  }
  return 0;
}
