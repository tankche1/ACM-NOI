// UVa11520 Fill the Square
// Rujia Liu
#include<cstdio>
#include<cstring>
const int maxn = 10 + 5;
char grid[maxn][maxn];
int n;
int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%s", grid[i]);
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++) if(grid[i][j] == '.') {//û�������ĸ����Ҫ��
        for(char ch = 'A'; ch <= 'Z'; ch++) { 		//�����ֵ������γ���
          bool ok = true;
          if(i>0 && grid[i-1][j] == ch) ok = false; 	//���������ĸ��ͻ
          if(i<n-1 && grid[i+1][j] == ch) ok = false;
          if(j>0 && grid[i][j-1] == ch) ok = false;
          if(j<n-1 && grid[i][j+1] == ch) ok = false;
          if(ok) { grid[i][j] = ch; break; } //û�г�ͻ���������ֹͣ��������
        }
      }
    printf("Case %d:\n", kase);
    for(int i = 0; i < n; i++) printf("%s\n", grid[i]);
  }
  return 0;
}
