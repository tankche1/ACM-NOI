// UVa11361 Investigating Div-Sum Property ������ƪ���������޴˴��룩
// Rujia Liu
#include<cstdio>
#include<cstring>
using namespace std;

int MOD; // ��Ŀ�н�k������ΪMOD�����ô��������
int pow10[10];

// ����n����MOD������������0~MOD-1
int mod(int n) {
  return (n % MOD + MOD) % MOD;
}

// ��d�����֣�����֮�ͳ���k������Ϊm1�������������k������Ϊm2
int memo[11][90][90];
int f(int d, int m1, int m2) {
  if(d == 0) return m1 == 0 && m2 == 0 ? 1 : 0;

  int& ans = memo[d][m1][m2];
  if(ans >= 0) return ans;
  ans = 0;
  for(int x = 0; x <= 9; x++)
    ans += f(d-1, mod(m1-x), mod(m2-x*pow10[d-1]));
  return ans;
}

// ͳ��0~n-1���������������������������ϵķ�����һ����룬��û�б�������
int sumf(int n) {
  char digits[11];
  sprintf(digits, "%d", n);
  int nd = strlen(digits);

  int base = 0; // ��ǰ�������߽�
  int sumd = 0; // ��ǰ�������߽�����ֺ�
  int ans = 0;
  for(int i = 0; i < nd; i++) { // ��i������(i>=0)
    int na = nd - 1 - i; // �Ǻŵĸ���
    for(int d = 0; d < digits[i] - '0'; d++) {
      int cnt = f(na, mod(-sumd - d), mod(-base - d*pow10[na]));
      ans += cnt;
    }
    base += (digits[i] - '0') * pow10[na];
    sumd += (digits[i] - '0');
  }
  return ans;
}

int main() {
  pow10[0] = 1;
  for(int i = 1; i <= 9; i++) pow10[i] = pow10[i-1] * 10;

  int T;
  scanf("%d", &T);
  while(T--) {
    int a, b;
    scanf("%d%d%d", &a, &b, &MOD);
    memset(memo, -1, sizeof(memo));
    if(MOD > 85) printf("0\n"); // ���ֺ����Ϊ1+9*9=82�����MOD���ڴ�ֵ��һ���޽�
    else printf("%d\n", sumf(b+1) - sumf(a));
  }
  return 0;
}
