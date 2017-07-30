#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define LL long long
struct Point
{
    int x,y;
    bool operator <(const Point &b)const
    {
        if((LL)y*b.y<0)return y>b.y;
        if(b.y<0&&y==0)return true;
        return ((LL)x*b.y-(LL)b.x*y)>0;
    }
}p[100000+10],po[100000+10];
Point operator -(const Point &a,const Point &b)
{
    Point c;
    c.x=a.x-b.x;c.y=a.y-b.y;
    return c;
}
long long Cross(const Point &a,const Point &b)
{
    return (LL)a.x*b.y-(LL)b.x*a.y;
}
long long Dot(const Point &a,const Point &b)
{
    return (LL)a.x*b.x+(LL)b.y*a.y;
}
int n,tail;
bool vis[100000+10];
long long ans=0,ans2=0;
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&p[i].x,&p[i].y);
        }
        ans=((LL)n*(n-1)*(n-2))/6;ans2=0;
        for(int i=1;i<=n;i++)
        {
            tail=0;
            for(int j=1;j<=n;j++)
            {
                if(i!=j)po[tail++]=p[j]-p[i];
            }
            sort(po,po+tail);
            for(int i=0;i<tail;i++)vis[i]=0;
            //for(int j=0;j<tail;j++)cerr<<po[j].x<<" "<<po[j].y<<" ";
            //cerr<<endl;
            int fr=0,be=tail-1,num=0;
            if(fr==0){vis[fr]=true;fr++;if(fr==tail)fr=0;num++;}
            while(Cross(po[0],po[fr])>=0&&Dot(po[fr],po[0])>0&&!vis[fr]){vis[fr]=true;fr++;if(fr==tail)fr=0;num++;}
            while(Cross(po[0],po[be])<=0&&Dot(po[be],po[0])>0&&!vis[be]){vis[be]=true;be--;if(be==-1)be=tail-1;num++;}
            be++;if(be==tail)be=0;
            ans2+=tail-num;//cerr<<num<<endl;
            for(int j=1;j<tail;j++)
            {
                while(Cross(po[j],po[be])>0||Dot(po[be],po[j])<=0&&be!=j){vis[be]=false;be++;if(be==tail)be=0;num--;}
                while(Cross(po[j],po[fr])>=0&&Dot(po[fr],po[j])>0&&!vis[fr]){vis[fr]=true;fr++;if(fr==tail)fr=0;num++;}
                ans2+=tail-num;
                //cerr<<num<<endl;
            }
        }
        ans2/=2;
        ans-=ans2;
        cout<<ans<<endl;
    }
    return 0;
}
