// LA3704 Cellular Automaton
// Rujia Liu
#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;

int MOD;

typedef vector<int> CirculantMatrix;

CirculantMatrix operator * (const CirculantMatrix& a, const CirculantMatrix& b) {
  int n = a.size();
  assert(b.size() == n);
  CirculantMatrix c(n);
  for(int i = 0; i < n; i++) { // ����C(0,i)
    c[i] = 0;
    for(int j = 0; j < n; j++) // �ۼ�A(0,j)*B(j,i)
      c[i] = ((long long)a[j]*b[(i-j+n)%n] + c[i]) % MOD; // ��j�����ɵ�0��ѭ������jλ�õ�
  }
  return c;
}

// ����a^k��ֵ��Ҫ��a֧��*�����
template<typename T>
T fast_pow(const T& a, int k) {
  assert(k > 0);
  if(k == 1) return a;
  T b = fast_pow(a, k/2);
  b = b * b;
  if(k % 2 == 1) b = b * a;
  return b;
}

int main() {
  int n, m, d, k;
  while(scanf("%d%d%d%d", &n, &m, &d, &k) == 4) {
    MOD = m;
    CirculantMatrix mat(n);
    for(int i = 0; i < n; i++)
      mat[i] = min(i, n - i) <= d ? 1 : 0; // �����0�ľ���<=d��λ��ϵ����Ϊ1������Ϊ0

    CirculantMatrix v(n); // ���԰ѳ�ʼ״̬����ѭ��������м���
    for(int i = 0; i < n; i++) scanf("%d", &v[i]);
    v = v * fast_pow(mat, k);

    printf("%d", v[0]);
    for(int i = 1; i < n; i++) printf(" %d", v[i]);
    printf("\n");
  }
  return 0;
}
