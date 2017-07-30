#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
char a[11][11];
int dd[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
int conbo,sum;
int lzm[11][11];
bool vis[11][11];
char tpath[11],path[11];
int nowi,nowj,ansi,ansj;
bool Check()
{
    for(int i=1;i<=5;++i)
        for(int j=1;j<=6;++j)
            if(a[i][j]!=0)
            {
                if(a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j]) return true;
                if(a[i][j]==a[i][j+1]&&a[i][j]==a[i][j+2]) return true;
            }
    return false;
}
void D(int i,int j,int num)
{
    lzm[i][j]=num;
    for(int x=0;x<4;++x)
    {
        int ii=i+dd[x][0],jj=j+dd[x][1];
        if(ii>5||ii<1||jj>6||jj<1||lzm[ii][jj]||a[ii][jj]!=a[i][j]) continue;
        D(ii,jj,num);
    }
    return;
}
void solve()
{
    char ta[11][11];
    for(int i=1;i<=5;++i)
        for(int j=1;j<=6;++j)
            ta[i][j]=a[i][j];
    int tconbo=0,tsum=0;
    bool used[33];
    while(Check())
    {
        memset(lzm,0,sizeof lzm);
        memset(used,0,sizeof used);
        memset(vis,0,sizeof vis);
        int cnt=0;
        for(int i=1;i<=5;++i)
            for(int j=1;j<=6;++j)
                if(a[i][j]!=0&&!lzm[i][j])
                    D(i,j,++cnt);
        for(int i=1;i<=5;++i)
            for(int j=1;j<=6;++j)
                if(a[i][j]!=0)
                {
                    if(a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j])  vis[i][j]=vis[i+1][j]=vis[i+2][j]=true;
                    if(a[i][j]==a[i][j+1]&&a[i][j]==a[i][j+2])  vis[i][j]=vis[i][j+1]=vis[i][j+2]=true;
                    if(vis[i][j])
                    {
                        if(!used[lzm[i][j]])
                        {
                            tconbo++;
                            used[lzm[i][j]]=true;
                        }
                        tsum++;
                    }
                }
        for(int j=1;j<=6;++j)
        {
            int l=0;
            for(int i=5;i>=1;--i)
            {
                if(vis[i][j]) {l++;a[i][j]=0;}
                else {char t=a[i][j];a[i][j]=0;a[i+l][j]=t;}
            }
        }
    }
    if(tconbo>conbo||(tconbo==conbo&&tsum>sum))
    {
        conbo=tconbo;
        sum=tsum;
        for(int i=1;i<=9;++i)
            path[i]=tpath[i];
        ansi=nowi;
        ansj=nowj;
    }
    for(int i=1;i<=5;++i)
        for(int j=1;j<=6;++j)
            a[i][j]=ta[i][j];
    return;
}
void DFS(int i,int j,int k,int last)
{
    if(k>1) solve();
    if(k>9)
        return;
    for(int x=0;x<4;++x)
        if((x^1)!=last)
        {
            int ii=i+dd[x][0],jj=j+dd[x][1];
            if(ii>5||ii<1||jj>6||jj<1) continue;
            if(x==0) tpath[k]='U';
            else if(x==1) tpath[k]='D';
            else if(x==2) tpath[k]='R';
            else tpath[k]='L';
            swap(a[i][j],a[ii][jj]);
            DFS(ii,jj,k+1,x);
            swap(a[i][j],a[ii][jj]);
            tpath[k]=0;
        }
    return;
}
int main()
{
    int T;
    cin>>T;
    for(int ii=1;ii<=T;++ii)
    {
        for(int i=1;i<=5;++i)
            scanf("%s",a[i]+1);
        for(int i=1;i<=5;++i)
            for(int j=1;j<=6;++j)
            {
                nowi=i;
                nowj=j;
            //    cout<<i<<' '<<j<<endl;
                DFS(i,j,1,6);
            }
        int len=strlen(path+1);
        printf("Case #%d:\n",ii);
        printf("Combo:%d Length:%d\n",conbo,len);
        printf("%d %d\n",ansi,ansj);
        if(len) printf("%s\n",path+1);
    }
    return 0;
}
/*
1
CFFLLW
CPDPDC
FLDWFD
LFCFCD
CDPLWL
*/
