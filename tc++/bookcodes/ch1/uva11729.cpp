// UVa11729 Commando War
// Rujia Liu
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

struct Job {
  int j, b;
  bool operator < (const Job& x) const { // ��������ء���Ҫ����const���η�
    return j > x.j;
  }
};

int main() {
  int n, b, j, kase = 1;
  while(scanf("%d", &n) == 1 && n) {
    vector<Job> v;
    for(int i = 0; i < n; i++) {
      scanf("%d%d", &b, &j); v.push_back((Job){j,b});
    }
    sort(v.begin(), v.end()); //ʹ��Job���Լ��� < ���������
    int s = 0;
    int ans = 0;
    for(int i = 0; i < n; i++) {
      s += v[i].b;  //��ǰ����Ŀ�ʼִ��ʱ��
      ans = max(ans, s+v[i].j);	//��������ִ�����ʱ������ʱ��
    }
    printf("Case %d: %d\n", kase++, ans);
  }
  return 0;
}
