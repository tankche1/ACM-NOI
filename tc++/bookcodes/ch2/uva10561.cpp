// UVa10561 Treblecross ������ƪ���������޴˴��룩
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 200;
int g[maxn + 10];

bool winning(const char* state) {
  int n = strlen(state);
  for(int i = 0; i < n-2; i++)
    if(state[i] == 'X' && state[i+1] == 'X' && state[i+2] == 'X') return false; // �Ѿ������

  int no[maxn+1]; // no[i] = 1��ʾ�±�Ϊi�ĸ����ǡ�����������ĳ��'X'�ľ��벻����2��
  memset(no, 0, sizeof(no));
  no[n] = 1; // �ڱ�
  for(int i = 0; i < n; i++) if(state[i] == 'X') {
    for(int d = -2; d <= 2; d++)
      if(i+d >= 0 && i+d < n) {
        if(d != 0 && state[i+d] == 'X') return true; // ���������벻����2��'X'��һ������ȡʤ
        no[i+d] = 1;
      }
  }

  int sg = 0;
  int start = -1; // ��ǰ����������
  for(int i = 0; i <= n; i++) { // ע��Ҫѭ�������ڱ���Ϊֹ
    if(start < 0 && !no[i]) start = i; // �µĿ�
    if(no[i] && start >= 0) sg ^= g[i-start]; // ��ǰ�����
    if(no[i]) start = -1;
  }
  return sg != 0;
}

int mex(vector<int>& s) {
  if(s.empty()) return 0;
  sort(s.begin(), s.end());
  if(s[0] != 0) return 0;
  for(int i = 1; i < s.size(); i++)
    if(s[i] > s[i-1]+1) return s[i-1]+1;
  return s[s.size()-1] + 1;
}

// Ԥ�������g����
void init() {
  g[0] = 0;
  g[1] = g[2] = g[3] = 1;
  for(int i = 4; i <= maxn; i++) {
    vector<int> s;
    s.push_back(g[i-3]); // ����ߣ��±�Ϊ0�ĸ��ӣ�
    s.push_back(g[i-4]); // �±�Ϊ1�ĸ���
    if(i >= 5) s.push_back(g[i-5]);   // �±�Ϊ2�ĸ���
    for(int j = 3; j < i-3; j++)      // �±�Ϊ3~i-3�ĸ���
      s.push_back(g[j-2] ^ g[i-j-3]); // �����j-2�����ӣ��ұ���i-j-3�ĸ���
    g[i] = mex(s);
  }
}

int main() {
  init();

  int T;
  scanf("%d", &T);
  while(T--) {
    char state[maxn + 10];
    scanf("%s", state);
    int n = strlen(state);
    if(!winning(state)) printf("LOSING\n\n");
    else {
      printf("WINNING\n");
      vector<int> moves;
      for(int i = 0; i < n; i++) if(state[i] == '.') {
        state[i] = 'X';
        if(!winning(state)) moves.push_back(i+1);
        state[i] = '.';
      }
      printf("%d", moves[0]);
      for(int i = 1; i < moves.size(); i++) printf(" %d", moves[i]);
      printf("\n");
    }
  }
  return 0;
}
