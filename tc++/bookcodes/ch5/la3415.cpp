// LA3415 Guardian of Decency
// Rujia Liu
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500 + 5; // ���ඥ��������Ŀ

// ����ͼ������ƥ�䣬�ڽӾ���д��
struct BPM {
  int n, m;               // ���Ҷ������
  int G[maxn][maxn];      // �ڽӱ�
  int left[maxn];         // left[i]Ϊ�ұߵ�i�����ƥ����ţ�-1��ʾ������
  bool T[maxn];           // T[i]Ϊ�ұߵ�i�����Ƿ��ѱ��

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    memset(G, 0, sizeof(G));
  }

  bool match(int u){
    for(int v = 0; v < m; v++) if(G[u][v] && !T[v]) {
      T[v] = true;
      if (left[v] == -1 || match(left[v])){
        left[v] = u;
        return true;
      }
    }
    return false;
  }

  // �����ƥ��
  int solve() {
    memset(left, -1, sizeof(left));
    int ans = 0;
    for(int u = 0; u < n; u++) { // ����߽��u��ʼ����
      memset(T, 0, sizeof(T));
      if(match(u)) ans++;
    }
    return ans;
  }

};

BPM solver;

#include<iostream>
#include<string>
using namespace std;

struct Student {
  int h;
  string music, sport;
  Student(int h, string music, string sport):h(h), music(music), sport(sport) {}
};

bool conflict(const Student& a, const Student& b) {
  return abs(a.h - b.h) <= 40 && a.music == b.music && a.sport != b.sport;
}

int main(){
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<Student> male, female;
    for(int i = 0; i < n; i++) {
      int h;
      string gender, music, sport;
      cin >> h >> gender >> music >> sport;
      if(gender[0] == 'M') male.push_back(Student(h, music, sport));
      else female.push_back(Student(h, music, sport));
    }
    int x = male.size();
    int y = female.size();
    solver.init(x, y);
    for(int i = 0; i < x; i++)
      for(int j = 0; j < y; j++)
        if(conflict(male[i], female[j])) solver.G[i][j] = 1;
    printf("%d\n", x + y - solver.solve());
  }
  return 0;
}
