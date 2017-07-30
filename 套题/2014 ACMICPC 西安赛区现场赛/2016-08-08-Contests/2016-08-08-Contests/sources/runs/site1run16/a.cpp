
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int T;
int n;
int d[110];
int main()
{
  scanf("%d",&T);
  for(int C = 1; C <= T; C++)
  {
      scanf("%d",&n);
      for(int i = 1; i <= n; i++) scanf("%d",&d[i]);
      int flag = 1;
      for(int i = 1; i <= n; i++)
      if(d[i]%3)
      {
          flag = 0;
          break;
      }
      printf("Case #%d: %s\n",C,flag?"Yes":"No");
  }
  return 0;
}
