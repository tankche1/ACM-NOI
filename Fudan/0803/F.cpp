#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int dd[4][2]={{-1,1},{1,1},{-1,-1},{1,-1}};
char map[15][15];
int T;
int ans=0;
void DFS(int x,int y,int step)
{
    ans=max(ans,step);
    for(int i=0;i<4;++i)
    {
        int tx=x+dd[i][0],ty=y+dd[i][1];
        if(tx<0||tx>9||ty<0||ty>9) continue;
        if(map[tx][ty]!='B') continue;
        tx=tx+dd[i][0],ty=ty+dd[i][1];
        if(tx<0||tx>9||ty<0||ty>9) continue;
        if(map[tx][ty]!='#') continue;
        map[tx-dd[i][0]][ty-dd[i][1]]='#';
        DFS(tx,ty,step+1);
        map[tx-dd[i][0]][ty-dd[i][1]]='B';
    }
    return;
}
int main()
{
    cin>>T;
    while(T--)
    {
        ans=0;
        for(int i=0;i<10;++i)
            scanf("%s",map[i]);
        for(int i=0;i<10;++i)
            for(int j=0;j<10;++j)
              if(map[i][j]=='W')
              {
                  map[i][j]='#';
                DFS(i,j,0);
                map[i][j]='W';
              }
        printf("%d\n",ans);
    }
    return 0;
}
