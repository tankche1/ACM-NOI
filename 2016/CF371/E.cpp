# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;

int m,n;
int a[maxn],b[maxn];
int f[maxn];

bool check(int len){
    //1Íù×ó
    f[1]=b[1];
    bool ok=true;
    for(int i=2;i<=n;i++){
        if(f[i-1]+len+1>=b[i]) f[i]=max(b[i],f[i-1]);
        else {ok=false;break;}
        if(f[i-1]>=b[i]-1) f[i]=max(f[i],b[i]+len);

        if(i>2&&f[i-2]+len+1>=b[i]) f[i]=max(f[i],b[i-1]+len);
    }
    if(ok&&f[n]+len>=m) return true;
    ok=true;
    //1ÍùÓÒ 2Íù×ó
    f[2]=max(b[2],b[1]+len);
    for(int i=3;i<=n;i++){
        if(f[i-1]+len+1>=b[i]) f[i]=max(b[i],f[i-1]);
        else {ok=false;break;}
        if(f[i-1]>=b[i]-1) f[i]=max(f[i],b[i]+len);

        if(f[i-2]+len+1>=b[i]) f[i]=max(f[i],b[i-1]+len);
    }
    if(ok&&f[n]+max(0,len-(b[2]-1))>=m) return true;
    return false;
}

int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    if(n==1) {printf("%d\n",m-1);return 0;}
    int pos=1,best=a[1]-1+m-a[n];

    for(int i=2;i<=n;i++) if(a[i]-a[i-1]-1>best) best=a[i]-a[i-1]-1,pos=i;
    int t=a[pos]-1;
    for(int i=1;i<=n;i++) {a[i]=a[i]-t;if(a[i]<=0) a[i]+=m;}
    for(int i=pos;i<=n;i++) b[i-pos+1]=a[i];
    for(int i=1;i<pos;i++) b[n-pos+1+i]=a[i];

    int L=(best+1)/2,R=best-1,M;
    while(L<=R){
        M=(L+R)>>1;
        if(check(M)) R=M-1;
        else L=M+1;
    }
    printf("%d\n",R+1);

    return 0;
}
