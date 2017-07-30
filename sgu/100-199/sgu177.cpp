#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
int parents[maxn][maxn];
bool vis[maxn][maxn];
int Find(int r,int x)
{
    return parents[r][x]==x?x:parents[r][x]=Find(r,parents[r][x]);
}
struct Paint
{
    int x1,y1,x2,y2;
    int colors;
    void readit()
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    }
    void change()
    {
        if(x1>x2) swap(x1,x2);
        if(y1>y2) swap(y1,y2);
    }
}paints[maxn*5];
int main()
{

    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    char str[5];
    for(int i=0;i<m;++i)
    {
        paints[i].readit();
        paints[i].change();
        scanf("%s",str);
        if(str[0]=='b') paints[i].colors=1;
        else paints[i].colors=0;
    }
    for(int i=1;i<=n;++i)
      for(int j=1;j<=n;++j)
         parents[i][j]=j;
    memset(vis,0,sizeof(vis));
    int total=n*n;
    int now,f;
    for(int i=m-1;i>=0;--i)
    {
        for(int j=paints[i].x1;j<=paints[i].x2;++j)
        {
            now=paints[i].y1;
            while(now<=paints[i].y2)
            {
                f=Find(j,now);
                if(f==now&&!vis[j][now])
                {
                    vis[j][now]=true;
                    parents[j][now]=paints[i].y2;
                    if(paints[i].colors) total--;
                    now++;

                }
                else now=f+1;
            }
        }
    }
    printf("%d\n",total);
    return 0;
}
