#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

typedef long long LL;
LL k,n,num[100001];
int len,z[1000],now_r,delta,sum;

int main()
{
    for(int i=1;i<=100000;i++)num[i]=num[i-1]+i;
    while(cin>>k)
    {
        if(k<=100000)
        {
            printf("%d\n",k);
            for(int i=1;i<k;i++)printf("1 ");
            printf("1\n");
            continue;
        }
        n=1;
        while(num[n]<k)n++;
        delta=num[n]-k;
        len=sum=0;
        //cerr<<"!"<<endl;
        for(int i=100000;i>0;i--)
            if(num[i]<=delta)
            {
                z[++len]=i;
                delta-=num[i];
                sum+=i;
                i++;
            }
        //for(int i=1;i<=len;i++)printf("%d\n",z[i]);
        now_r=n-sum;
        printf("%d\n",n);
        for(int i=1;i<=n-sum;i++)printf("%d ",i);
        for(int i=1;i<=len;i++)
        {
            for(int j=now_r-z[i]+1;j<=now_r;j++)printf("%d ",j);
            now_r-=z[i];
        }
        printf("\n");
    }
    return 0;
}
