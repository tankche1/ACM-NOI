// UVa11549 Calculator Conundrum
// Rujia Liu
#include<iostream>
using namespace std;

int buf[100];

int next(int n, int k) {
  if(!k) return 0;
  long long k2 = (long long)k * k;
  int L = 0;
  while(k2 > 0) { buf[L++] = k2 % 10; k2 /= 10; } // ���벢����k2�ĸ�������
  if(n > L) n = L;
  int ans = 0;
  for(int i = 0; i < n; i++) // ��ǰmin{n,L}λ�������
    ans = ans * 10 + buf[--L];
  return ans;
}

int main() {
  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    int ans = k;
    int k1 = k, k2 = k;
    do {
      k1 = next(n, k1); // С��1
      k2 = next(n, k2); if(k2 > ans) ans = k2; // С��2����һ��
      k2 = next(n, k2); if(k2 > ans) ans = k2; // С��2���ڶ���
    } while(k1 != k2); // ׷���Ժ��ֹͣ
    cout << ans << endl;
  }
  return 0;
}
