// UVa11806 Cheerleaders
// Rujia Liu
#include<cstdio>
#include<cstring>
using namespace std;

const int MOD = 1000007;
const int MAXK = 500;
int C[MAXK+10][MAXK+10];

int main() {
  memset(C, 0, sizeof(C));
  C[0][0] = 1;
  for(int i = 0; i <= MAXK; i++) {
    C[i][0] = C[i][i] = 1; // ǧ��Ҫ����д�߽�����
    for(int j = 1; j < i; j++)
      C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
  }

  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    int n, m, k, sum = 0;
    scanf("%d%d%d", &n, &m, &k);
    for(int S = 0; S < 16; S++) { // ö������16�֡����䷽ʽ��
      int b = 0, r = n, c = m; // b����ͳ�Ƽ��ϵĸ�����r��c�ǿ��Է��õ�������
      if(S&1) { r--; b++; } // ��һ��û��ʯͷ�����Է�ʯͷ������r��1
      if(S&2) { r--; b++; }
      if(S&4) { c--; b++; }
      if(S&8) { c--; b++; }
      if(b&1) sum = (sum + MOD - C[r*c][k]) % MOD; // ������������������
      else sum = (sum + C[r*c][k]) % MOD;          // ż�������������ӷ�
    }
    printf("Case %d: %d\n", kase, sum);
  }
  return 0;
}
