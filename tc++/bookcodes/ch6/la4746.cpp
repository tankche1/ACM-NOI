// LA4746 Decrypt Messages
// Rujia Liu
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long LL;

//// ����ʱ�䲿��

const int SECONDS_PER_DAY = 24 * 60 * 60;

const int num_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap(int year) {
  if (year % 400 == 0) return true;
  if (year % 4 == 0) return year % 100 != 0;
  return false;
}

int leap_second(int year, int month) {
  return ((year % 10 == 5 || year % 10 == 8) && month == 12) ? 1 : 0;
}

void print(int year, int month, int day, int hh, int mm, int ss) {
  printf("%d.%02d.%02d %02d:%02d:%02d\n", year, month, day, hh, mm, ss);
}

void print_time(LL t) {
  int year = 2000;
  while(1) {
    int days = is_leap(year) ? 366 : 365;
    LL sec = (LL)days * SECONDS_PER_DAY + leap_second(year, 12);
    if(t < sec) break;
    t -= sec;
    year++;
  }

  int month = 1;
  while(1) {
    int days = num_days[month-1];
    if(is_leap(year) && month == 2) days++;
    LL sec = (LL)days * SECONDS_PER_DAY + leap_second(year, month);
    if(t < sec) break;
    t -= sec;
    month++;
  }

  if(leap_second(year, month) && t == 31 * SECONDS_PER_DAY)
    print(year, 12, 31, 23, 59, 60);
  else {
    int day = t / SECONDS_PER_DAY + 1;
    t %= SECONDS_PER_DAY;
    int hh = t / (60*60);
    t %= 60*60;
    int mm = t / 60;
    t %= 60;
    int ss = t;
    print(year, month, day, hh, mm, ss);
  }
}

//// ���۲���

LL gcd(LL a, LL b) {
  return b ? gcd(b, a%b) : a;
}

// ��d = gcd(a, b)���Լ�����ax+by=d��(x,y)��ע�⣬x��y����Ϊ������
// ��չeuclid�㷨��
void gcd(LL a, LL b, LL& d, LL& x, LL& y) {
  if(!b){ d = a; x = 1; y = 0; }
  else{ gcd(b, a%b, d, y, x); y -= x*(a/b); }
}

// ע�⣬����ֵ�����Ǹ���
int pow_mod(LL a, LL p, int MOD) {
  if(p == 0) return 1;
  LL ans = pow_mod(a, p/2, MOD);
  ans = ans * ans % MOD;
  if(p%2) ans = ans * a % MOD;
  return ans;
}

// ע�⣬����ֵ�����Ǹ���
int mul_mod(LL a, LL b, int MOD) {
  return a * b % MOD;
}

// ��ax = 1 (mod MOD) �Ľ⣬����a��MOD���ء�
// ע�⣬����MOD��һ��Ϊ��������˲���ֱ����pow_mod(a, MOD-2, MOD)���
// �ⷨ������ax + MODy = 1�Ľ�(x,y)����xΪ����
int inv(LL a, int MOD) {
  LL d, x, y;
  gcd(a, MOD, d, x, y);
  return (x + MOD) % MOD; // �����x�����Ǹ��������Ҫ����
}

// ��ģ���̣�����ɢ������a^x = b��Ҫ��MODΪ����
// �ⷨ��Shank�Ĵ�С���㷨
int log_mod(int a, int b, int MOD) {
  int m, v, e = 1, i;
  m = (int)sqrt(MOD);
  v = inv(pow_mod(a, m, MOD), MOD);
  map<int,int> x;
  x[1] = 0;
  for(i = 1; i < m; i++){ e = mul_mod(e, a, MOD); if (!x.count(e)) x[e] = i; }
  for(i = 0; i < m; i++){
    if(x.count(b)) return i*m + x[b];
    b = mul_mod(b, v, MOD);
  }
  return -1;
}

// ����MOD����һ������������ĳһ��ԭ����phiΪMOD��ŷ������ֵ����MODΪ������phi=MOD-1��
// �ⷨ������phi(MOD)������������p���������m^(phi/p) mod MOD��������1����m��MOD��ԭ��
int get_primitive_root(int MOD, int phi) {
  // ����phi������������
  vector<int> factors;
  int n = phi;
  for(int i = 2; i*i <= n; i++) {
    if(n % i != 0) continue;
    factors.push_back(i);
    while(n % i == 0) n /= i;
  }
  if(n > 1) factors.push_back(n);

  while(1) {
    int m = rand() % (MOD-2) + 2; // m = 2~MOD-1
    bool ok = true;
    for(int i = 0; i < factors.size(); i++)
      if(pow_mod(m, phi/factors[i], MOD) == 1) { ok = false; break; }
    if(ok) return m;
  }
}

// ������ģ���� ax = b (mod n)���������н⣨ģnʣ��ϵ��
// �ⷨ����d = gcd(a, n)������ͬʱ����d���a'x = b' (mod n')�����ڴ�ʱgcd(a',n')=1������ͬʱ���a'��ģn'�е��漴�ɣ�����ģn'ʣ��ϵ�еĽ�ת��Ϊģnʣ��ϵ
vector<LL> solve_linear_modular_equation(int a, int b, int n) {
  vector<LL> ans;
  int d = gcd(a, n);
  if(b % d != 0) return ans;
  a /= d; b /= d;
  int n2 = n / d;
  int p = mul_mod(inv(a, n2), b, n2);
  for(int i = 0; i < d; i++)
    ans.push_back(((LL)i * n2 + p) % n);
  return ans;
}

// ��ߴ�ģ���� x^q = a (mod p)���������н⣨ģnʣ��ϵ��
// �ⷨ����mΪp��һ��ԭ������x = m^y, a = m^z����m^qy = m^z(mod p)�����qy = z(mod p-1)��������ģ���̼���
vector<LL> mod_root(int a, int q, int p) {
  vector<LL> ans;
  if(a == 0) {
    ans.push_back(0);
    return ans;
  }
  int m = get_primitive_root(p, p-1); // p�����������phi(p)=p-1
  int z = log_mod(m, a, p);
  ans = solve_linear_modular_equation(q, z, p-1);
  for(int i = 0; i < ans.size(); i++)
    ans[i] = pow_mod(m, ans[i], p);
  sort(ans.begin(), ans.end());
  return ans;
}

int main() {
  int T, P, Q, A;
  cin >> T;
  for(int kase = 1; kase <= T; kase++) {
    cin >> P >> Q >> A;
    vector<LL> ans = mod_root(A, Q, P);
    cout << "Case #" << kase << ":" << endl;
    if (ans.empty()) {
      cout << "Transmission error" << endl;
    } else {
      for(int i = 0; i < ans.size(); i++) print_time(ans[i]);
    }
  }	
  return 0;
}
