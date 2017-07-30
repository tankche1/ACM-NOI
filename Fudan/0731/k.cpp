#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
#define maxn 5050
using namespace std;
struct node
{
    int a,sum;
    bool operator <(const node &b)const
    {
        return sum>b.sum||(sum==b.sum&&a>b.a);
    }
    node(int a,int sum)
    {
        this->a=a;
        this->sum=sum;
    }
};
int a,b,c,d;
int n,m;
int sum[maxn];
priority_queue<node>Q;
int gcd(int a,int b)
{
    int c=a;
    while(b)
    {
        a=b;
        b=c%b;
        c=a;
    }
    return a;
}
int main()
{
    freopen("kids.in","r",stdin);
    freopen("kids.out","w",stdout);
    cin>>a>>b>>c>>d;
    int k=gcd(b,c);
    m=b*c/k/b;
    n=b*c/k/c;
    k=1;
    while(m*k<=a||n*k<=d||m*k<c||n*k<b)
        k++;
    if(a*m*k%2==1||d*n*k%2==1) k++;
    m*=k;n*=k;
    printf("%d %d\n",m,n);
    for(int i=1;i<=m;++i)
    {
        for(int j=i+1;j<=m;++j)
            Q.push(node(j,sum[j]));
        while(sum[i]<a)
        {
            node t=Q.top();
            Q.pop();
            sum[i]++;
            sum[t.a]++;
            printf("%d %d\n",i,t.a);
        }
        while(!Q.empty()) Q.pop();
    }
    memset(sum,0,sizeof sum);
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
            Q.push(node(j,sum[j]));
        while(sum[i]<d)
        {
            node t=Q.top();
            Q.pop();
            sum[i]++;
            sum[t.a]++;
            printf("%d %d\n",i+m,t.a+m);
        }
        while(!Q.empty()) Q.pop();
    }
    int j=1;
    for(int i=1;i<=m;++i)
        for(int x=1;x<=b;++x)
        {
            printf("%d %d\n",i,j+m);
            j++;
            if(j>n) j=1;
        }
    return 0;
}
