#include<cmath>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
char mp[55][55];
bool check(int x,int y)
{
    return mp[x][y]=='G'||mp[x][y]=='R';
}
bool check2(int x,int y)
{
    return mp[x][y]=='G'||mp[x][y]=='B';
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%s",mp[i]+1);
        m=strlen(mp[1]+1);
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            int x=i,y=1;
            while(x<=n&&y<=m)
            {
                if((y==1||!check(x-1,y-1))&&check(x,y))
                {
                    ans++;
                }
                x++;y++;
            }
        }
        for(int i=2;i<=m;i++)
        {
            int x=1,y=i;
            while(x<=n&&y<=m)
            {
                if((x==1||!check(x-1,y-1))&&check(x,y))
                {
                    ans++;
                }
                x++;y++;
            }
        }
        for(int i=1;i<=n;i++)
        {
            int x=i,y=1;
            while(x>0&&y<=m)
            {
                if((y==1||!check2(x+1,y-1))&&check2(x,y))
                {
                    ans++;
                }
                x--;y++;
            }
        }
        for(int i=2;i<=m;i++)
        {
            int x=n,y=i;
            while(x>0&&y<=m)
            {
                if((x==n||!check2(x+1,y-1))&&check2(x,y))
                {
                    ans++;
                }
                x--;y++;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
