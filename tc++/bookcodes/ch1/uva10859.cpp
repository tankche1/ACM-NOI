// UVa10859 Placing Lampposts
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

vector<int> adj[1010]; // ɭ����ϡ��ģ���������ʡ�ռ䣬ö�����ڽ��Ҳ����
int vis[1010][2], d[1010][2], n, m;

int dp(int i, int j, int f) {
  // ��DFS��ͬʱ���ж�̬�滮��f��i�ĸ���㣬��������״̬��
  if(vis[i][j]) return d[i][j];
  vis[i][j] = 1;
  int& ans = d[i][j];

  // �ŵ����ǺϷ�����
  ans = 2000; // �Ƶ�������1��x��2000
  for(int k = 0; k < adj[i].size(); k++)
    if(adj[i][k] != f) // ����жϷǳ���Ҫ�����˸����֮������ڽ������ӽ��
      ans += dp(adj[i][k], 1, i); // ע�⣬��Щ���ĸ������i
  if(!j && f >= 0) ans++; // ���i���Ǹ����Ҹ����û�ŵƣ���x��1

  if(j || f < 0) { // i�Ǹ������丸����ѷŵƣ�i�ſ��Բ��ŵ�
    int sum = 0;
    for(int k = 0; k < adj[i].size(); k++)
      if(adj[i][k] != f)
        sum += dp(adj[i][k], 0, i);
    if(f >= 0) sum++; // ���i���Ǹ�����x��1
    ans = min(ans, sum);
  }
  return ans;
}

int main() {
  int T, a, b;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) adj[i].clear();
    // adj�ﱣ������һ�����ݵ�ֵ���������
    for(int i = 0; i < m; i++) {
      scanf("%d%d", &a, &b);
      adj[a].push_back(b);
      adj[b].push_back(a); // ��Ϊ������ͼ
    }
    memset(vis, 0, sizeof(vis));
    int ans = 0;
    for(int i = 0; i < n; i++)
      if(!vis[i][0]) // �µ�һ����
        ans += dp(i,0,-1); // i����������˸���㲻���ڣ�-1��
    printf("%d %d %d\n", ans/2000, m-ans%2000, ans%2000); //��x����3������
  }
  return 0;
}
