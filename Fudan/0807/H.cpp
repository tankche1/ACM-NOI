#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define maxn 166
#define INF 0x3f3f3f3f
using namespace std;
int a[4];
int sum[maxn];
int n;
int f[3][maxn];
int From[3][maxn];
int main()
{
    int T;
    cin>>T;
    for(int ii=1;ii<=T;++ii)
    {
        scanf("%d",&n);
        memset(f,0x3f,sizeof f);
        memset(From,0,sizeof From);
        memset(sum,0,sizeof sum);
        for(int i=1;i<=n;++i)
        {
            int t;scanf("%d",&t);
            sum[t]++;
        }
        for(int i=160;i>=0;--i)
            sum[i]+=sum[i+1];
        for(int i=160;i>=2;--i)
            f[2][i]=abs(sum[i]-n/4);
        for(int i=1;i>=0;--i)
            for(int j=160-2+i;j>=i;--j)
                for(int k=j+1;k<=160-1+i;++k)
                    if(f[i+1][k]+abs(sum[j]-sum[k]-n/4)<f[i][j])
                    {
                        f[i][j]=f[i+1][k]+abs(sum[j]-sum[k]-n/4);
                        From[i][j]=k;
                    }
        int ans=INF,p=-1;
        for(int i=0;i<=158;++i)
            if(f[0][i]+abs(sum[0]-sum[i]-n/4)<ans)
            {
                ans=f[0][i]+abs(sum[0]-sum[i]-n/4);
                p=i;
            }
        printf("Case %d:",ii);
        for(int i=0;i<=2;++i)
        {
            printf(" %d",p-1);
            p=From[i][p];
        }
        printf("\n");
    }
    return 0;
}
