#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

const int maxlen=9;
const int dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};

struct sol
{
  int sx,sy,x,y,len,com,tot;
  int r[20];
};

char o[150][10][10],a[10][10];
char s[500];
int mark[100][100];
sol ans[150],usr;

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

void checksol(sol& now)
{
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
}

FILE* fres = NULL;
string res_name;
void yes()
{
  // <TODO>: Return YES to PC^2.
  fprintf(fres, "<?xml version=\"1.0\"?>\n");
  fprintf(fres, "<result outcome=\"%s\" security=\"%s\"/>\n", "Yes", res_name.c_str());
  fprintf(stderr,"Judged as: Yes\n");
  fclose(fres);
}

void no()
{
  fprintf(fres, "<?xml version=\"1.0\"?>\n");
  fprintf(fres, "<result outcome=\"%s\" security=\"%s\"/>\n", "No - Wrong Answer", res_name.c_str());
  fprintf(stderr,"Judged as: No - Wrong Answer\n");
  fclose(fres);
  exit(0);
}

int main(int argc, char* argv[])
{
  FILE* fin = fopen(argv[1],"rt");
  FILE* fout = fopen(argv[2],"rt");
  FILE* fans = fopen(argv[3],"rt");
  fres = fopen(argv[4],"wt");
  res_name = string(argv[4]);

  //读入输入数据
  //FILE* f=freopen("pad.in","r",stdin);
  int t;
  fscanf(fin,"%d",&t);
  memset(o,'.',sizeof(o));
  for(int cnt=1;cnt<=t;++cnt)
  {
    for(int i=1;i<6;++i)
      fscanf(fin,"%s",o[cnt][i]+1);
  }
  //fclose(f);

  //读入标准答案
  //f=freopen("pad.ans","r",stdin);
  for(int cnt=1;cnt<=t;++cnt)
  {
    fscanf(fans,"%s",s);
    fscanf(fans,"%s",s);
    fscanf(fans,"%s",s);
    ans[cnt].com=0;
    for(int i=6;i<(int)strlen(s);++i)
      ans[cnt].com=ans[cnt].com*10+s[i]-'0';
    fscanf(fans,"%s",s);
    ans[cnt].len=0;
    for(int i=7;i<(int)strlen(s);++i)
      ans[cnt].len=ans[cnt].len*10+s[i]-'0';
    fscanf(fans,"%d %d",&ans[cnt].sx,&ans[cnt].sy);
    fscanf(fans,"%s",s);
    for(int i=0;i<(int)strlen(s);++i)
    {
      if(s[i]=='U')
        ans[cnt].r[i+1]=0;
      if(s[i]=='L')
        ans[cnt].r[i+1]=1;
      if(s[i]=='R')
        ans[cnt].r[i+1]=2;
      if(s[i]=='D')
        ans[cnt].r[i+1]=3;
    }
    memcpy(a,o[cnt],sizeof(o[cnt]));
    checksol(ans[cnt]);
  }
  //fclose(f);

  //读入并判定用户答案
  //f=freopen("pad.out","r",stdin);
  for(int cnt=1;cnt<=t;++cnt)
  {
    int cas;
    bool flag=true;
    fscanf(fout,"%s",s);
    if(strcmp(s,"Case")!=0) no();
    if(fgetc(fout) != ' ') no();
    if(fgetc(fout) != '#') no();
    cas=0;
    int CCCCC = 0;
    while((CCCCC=fgetc(fout)) != EOF && CCCCC >= '0' && CCCCC <= '9')
    {
      cas = cas * 10 + CCCCC - '0';
    }
    if(cas!=cnt) no();
    fscanf(fout,"%s",s);
    int ucom=0;
    for(int i=6;i<(int)strlen(s);++i)
      ucom=ucom*10+s[i]-'0';
    s[6]='\0';
    if(strcmp(s,"Combo:")!=0) no();
    fscanf(fout,"%s",s);
    usr.len=0;
    for(int i=7;i<(int)strlen(s);++i)
      usr.len=usr.len*10+s[i]-'0';
    s[7]='\0';
    if(strcmp(s,"Length:")!=0) no();
    fscanf(fout,"%d %d",&usr.sx,&usr.sy);
    if(!inrange(usr.sx,usr.sy)) no();
    fscanf(fout,"%s",s);
    for(int i=0;i<(int)strlen(s);++i)
    {
      if(s[i]=='U')
        usr.r[i+1]=0;
      else if(s[i]=='L')
        usr.r[i+1]=1;
      else if(s[i]=='R')
        usr.r[i+1]=2;
      else if(s[i]=='D')
        usr.r[i+1]=3;
      else
        no();
    }
    if((int)strlen(s)!=usr.len)
      no();
    if(flag)
    {
      flag=false;
      memcpy(a,o[cnt],sizeof(o[cnt]));
      checksol(usr);
      if((usr.com==ucom)&&(usr.com==ans[cnt].com)&&(usr.tot==ans[cnt].tot)&&(usr.len==ans[cnt].len))
        flag=true;
    }
    if(flag)
      {}
    else
      no();
  }
  if(fscanf(fout,"%*s") != EOF) no();
  yes();
  //fclose(f);
  return 0;
}
