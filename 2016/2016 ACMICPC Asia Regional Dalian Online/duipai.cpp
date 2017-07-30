#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define mod 1000000007
using namespace std;
typedef long long LL;
struct node
{
    int n,m;
    LL a[5][5];
    node(){}
    node (int n,int m)
    {
        this->n=n;
        this->m=m;
        memset(a,0,sizeof a);
    }

    node operator *(const node &b)
    {
        node c(n,b.m);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=b.m;++j)
                for(int k=1;k<=m;++k)
                    c.a[i][j]=(c.a[i][j]+a[i][k]*b.a[k][j])%mod;
        return c;
    }
}A,ans;

LL f(int k)
{
    if(k==0) return 1;
    A.n=A.m=2;
    A.a[1][1]=0;
    A.a[1][2]=A.a[2][1]=A.a[2][2]=1;
    ans.n=1;ans.m=2;
    ans.a[1][1]=1;ans.a[1][2]=2;
    k--;
    while(k)
    {
        if(k&1) ans=ans*A;
        A=A*A;
        k>>=1;
    }
    return ans.a[1][2];
}

LL solve(int k)
{
    if(k==1) return 1;
    else if(k==2) return 3;
    return (2*f(k-3)+f(k-2))%mod;
}

LL power(LL a,LL b)
{
    LL sum=1;
    while(b)
    {
        if(b&1) sum=sum*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return sum;

}

LL phi(int k)
{
    LL ret=k;
    int tk=k;
    for(int i=2;i*i<=k;++i)
        if(tk%i==0)
        {
            ret=ret*(i-1)/i;
            while(tk%i==0) tk/=i;
        }
    if(tk>1) ret=ret*(tk-1)/tk;
    return ret;
}

int main()
{
    //for(int i=1;i<=10;i++) printf("i:%d f:%I64d g:%I64d\n",i,f(i),solve(i));
    int n;
    LL ans=0;
    while(scanf("%d",&n)!=EOF)
    {
        ans=0;
        int cnt=0;
        if(n==1) {cout<<2<<endl;continue;}
        for(int i=1;i*i<=n;++i)
        {
            if(n%i==0)
            {
                ans+=solve(i)*phi(n/i)%mod;
                ans%=mod;
                if(i*i!=n) {
                    ans+=solve(n/i)*phi(i)%mod;
                }
                ans%=mod;
            }
        }
        ans=ans*power(n,mod-2)%mod;
        cout<<ans<<endl;
    }
    return 0;

}
