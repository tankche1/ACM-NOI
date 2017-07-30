// LA4119 Always an Integer ������ƪ���������޴˴��룩
// Rujia Liu
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<string>
#include<vector>
#include<iostream>
#include<cassert>
using namespace std;

struct Polynomial {
  vector<int> a, p; // ��i��Ϊa[i] * n^p[i]
  void parse_polynomial(string expr) { // ��������ʽ���������ţ�
    int i = 0, len = expr.size();
    while(i < len) { // ÿ��ѭ�������һ��a*n^p
      int sign = 1;
      if(expr[i] == '+') i++;
      if(expr[i] == '-') { sign = -1; i++; }
      int v = 0;
      while(i < len && isdigit(expr[i])) v = v * 10 + expr[i++] - '0'; // ϵ���ľ���ֵ
      if(i == len) { a.push_back(v); p.push_back(0); } // ������
      else {
        assert(expr[i] == 'n');
        if(v == 0) v = 1; // ��ϵ������1����
        v *= sign;
        if(expr[++i] == '^') { // ��ָ����
          a.push_back(v);
          v = 0; // ���v����������v����ָ��
          i++;
          while(i < len && isdigit(expr[i])) v = v * 10 + expr[i++] - '0';
          p.push_back(v);
        } else { // ��ָ����
          a.push_back(v); p.push_back(1);
        }
      }
    }
  }

  // ����f(x)����MOD������
  int mod(int x, int MOD) {
    int n = a.size();
    int ans = 0;
    for(int i = 0; i < n; i++) {
      int m = a[i];
      for(int j = 0; j < p[i]; j++) m = (long long)m * x % MOD; // ע��������
      ans = ((long long)ans + m) % MOD; // �ӷ�Ҳ���ܻ������
    }
    return ans;
  }
};

bool check(string expr) {
  int p = expr.find('/');
  Polynomial poly;
  poly.parse_polynomial(expr.substr(1, p-2));
  int D = atoi(expr.substr(p+1).c_str());
  for(int i = 1; i <= poly.p[0]+1; i++)
    if(poly.mod(i, D) != 0) return false;
  return true;
}

int main() {
  int kase = 1;
  string expr;
  while(cin >> expr) {
    if(expr[0] == '.') break;
    printf("Case %d: ", kase++);
    if(check(expr)) printf("Always an integer\n");
    else printf("Not always an integer\n");
  }
  return 0;
}
