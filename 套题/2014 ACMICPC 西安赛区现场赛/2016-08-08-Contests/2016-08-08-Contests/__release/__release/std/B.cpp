#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int maxlen=9;
const int dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
const char dir[4]={'U','L','R','D'};

struct sol
{
  int sx,sy,x,y,len,com,tot;
  int r[20];
};

char o[10][10],a[10][10];
int mark[10][10];
sol ans;
queue<sol> q;

bool inrange(int x,int y)
{
  return ((x>0)&&(x<6)&&(y>0)&&(y<7));
}

void floodfill(int x,int y,int c,int v)
{
  mark[x][y]=v;
  for(int i=0;i<4;++i)
  {
    int j=x+dx[i],k=y+dy[i];
    if((inrange(j,k))&&(mark[j][k]==c))
      floodfill(j,k,c,v);
  }
}

void check(sol now)
{
  memcpy(a,o,sizeof(o));
  int j=now.sx,k=now.sy,nj,nk;
  for(int i=1;i<=now.len;++i)
  {
    nj=j+dx[now.r[i]];
    nk=k+dy[now.r[i]];
    swap(a[j][k],a[nj][nk]);
    j=nj;
    k=nk;
  }
  now.com=now.tot=0;
  bool flag;
  do
  {
    flag=false;
    memset(mark,0,sizeof(mark));
    int cnt=0;
    for(int i=1;i<6;++i)
    {
      for(int j=3;j<7;++j)
      {
        if(a[i][j]=='.')
          continue;
        if((a[i][j-2]==a[i][j])&&(a[i][j-1]==a[i][j]))
        {
          if(!flag)
            flag=true;
          if(mark[i][j-2]==0)
          {
            mark[i][j-2]=mark[i][j-1]=mark[i][j]=++cnt;
          }
          else
            mark[i][j]=mark[i][j-2];
        }
      }
    }
    int col=cnt;
    if(flag)
    {
      for(int i=2;i<6;++i)
      {
        for(int j=1;j<7;++j)
        {
          if(a[i][j]=='.')
            continue;
          if((a[i-1][j]==a[i][j])&&(mark[i-1][j]>0)&&(mark[i][j]>0)&&(mark[i-1][j]!=mark[i][j]))
          {
            floodfill(i,j,mark[i][j],mark[i-1][j]);
            --cnt;
          }
        }
      }
    }
    for(int i=2;i<5;++i)
    {
      for(int j=1;j<7;++j)
      {
        if(a[i][j]=='.')
          continue;
        if((a[i-1][j]==a[i][j])&&(a[i+1][j]==a[i][j]))
        {
          if(!flag)
            flag=true;
          if((mark[i-1][j]==0)&&(mark[i][j]==0)&&(mark[i+1][j]==0))
          {
            mark[i-1][j]=mark[i][j]=mark[i+1][j]=++col;
            ++cnt;
          }
          else
          {
            int val=50;
            if((mark[i-1][j]>0)&&(mark[i-1][j]<val))
              val=mark[i-1][j];
            if((mark[i][j]>0)&&(mark[i][j]<val))
              val=mark[i][j];
            if((mark[i+1][j]>0)&&(mark[i+1][j]<val))
              val=mark[i+1][j];
            if(mark[i-1][j]==0)
              mark[i-1][j]=val;
            else if(mark[i-1][j]!=val)
            {
              floodfill(i-1,j,mark[i-1][j],val);
              --cnt;
            }
            if(mark[i][j]==0)
              mark[i][j]=val;
            else if(mark[i][j]!=val)
            {
              floodfill(i,j,mark[i][j],val);
              --cnt;
            }
            if(mark[i+1][j]==0)
              mark[i+1][j]=val;
            else if(mark[i+1][j]!=val)
            {
              floodfill(i+1,j,mark[i+1][j],val);
              --cnt;
            }
          }
        }
      }
    }
    if(flag)
    {
      for(int i=1;i<6;++i)
      {
        for(int j=2;j<7;++j)
        {
          if(a[i][j]=='.')
            continue;
          if((a[i][j-1]==a[i][j])&&(mark[i][j-1]>0)&&(mark[i][j]>0)&&(mark[i][j-1]!=mark[i][j]))
          {
            floodfill(i,j,mark[i][j],mark[i][j-1]);
            --cnt;
          }
        }
      }
    }
    now.com+=cnt;
    for(int j=1;j<7;++j)
    {
      for(int i=1;i<6;++i)
      {
        if(mark[i][j]>0)
        {
          ++now.tot;
          for(int k=i;k>0;--k)
          {
            if(a[k][j]=='.')
              break;
            a[k][j]=a[k-1][j];
          }
        }
      }
    }
  }while(flag);
  if(now.com>ans.com)
    ans=now;
  else if((now.com==ans.com)&&(now.tot>ans.tot))
    ans=now;
  else if((now.com==ans.com)&&(now.tot==ans.tot)&&(now.len<ans.len))
    ans=now;
}

int main(void)
{
  //freopen("pad.in","r",stdin);
  //freopen("pad.ans","w",stdout);
  int t;
  scanf("%d",&t);
  memset(o,'.',sizeof(o));
  for(int count=1;count<=t;++count)
  {
    for(int i=1;i<6;++i)
      scanf("%s",o[i]+1);
    ans.com=0;
    ans.len=maxlen+1;
    for(int i=1;i<6;++i)
    {
      for(int j=1;j<7;++j)
      {
        sol temp;
        temp.sx=temp.x=i;
        temp.sy=temp.y=j;
        temp.len=0;
        temp.r[0]=4;
        q.push(temp);
        while(!q.empty())
        {
          temp=q.front();
          q.pop();
          if(temp.len>0)
            check(temp);
          if(temp.len==maxlen)
            continue;
          for(int k=0;k<4;++k)
          {
            if(k+temp.r[temp.len]==3)
              continue;
            int nx=temp.x+dx[k],ny=temp.y+dy[k];
            if(!inrange(nx,ny))
              continue;
            sol nex=temp;
            nex.x=nx;
            nex.y=ny;
            nex.r[++nex.len]=k;
            q.push(nex);
          }
        }
      }
    }
    printf("Case #%d:\n",count);
    printf("Combo:%d Length:%d\n",ans.com,ans.len);
    printf("%d %d\n",ans.sx,ans.sy);
    for(int i=1;i<=ans.len;++i)
      printf("%c",dir[ans.r[i]]);
    printf("\n");
  }
  return 0;
}