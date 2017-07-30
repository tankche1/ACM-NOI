#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;
long long f[20000],sum[20000],a[20000];
int n;
int cmp(const void *a,const void *b)
{
    long long *aa=(long long *)a;
    long long *bb=(long long *)b;
    if (*aa>*bb) return 1;
    return -1;
}
void solve()
{
     long long i,j;
     scanf("%d\n",&n);
     for (i=1;i<=n;i++)
     scanf("%ld\n",&a[i]);
     
     qsort(&a[1],n,sizeof(a[0]),cmp);
     sum[0]=0;
     for (i=1;i<=n;i++)
     sum[i]=sum[i-1]+a[i];
     
     f[1]=0;
     for (i=2;i<=n;i++)
     f[i]=f[i-1]+a[i]*(i-1)-sum[i-1];
     
     cout<<f[n]*2<<endl;
}
int main(int argc, char *argv[])
{
    //freopen("Moo.in","r",stdin);
    //freopen("Moo.out","w",stdout);
    solve();
    return 0;
}


