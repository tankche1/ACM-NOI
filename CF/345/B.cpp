# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=500010;

int n;
LL a,b,T;
char s[maxn];
LL sum[maxn];

bool check(int num){
    if(num==0) return 1;
    LL ti=0;
    for(int i=0;i<=num-1;i++){
        ti=0;
        ti=ti+(sum[n]-sum[n-i])*b;
        ti=ti+sum[num-i]*b;
        ti+=num;
        ti+=min((LL)i*a,(LL)(num-i-1)*a)+(LL)i*a+(LL)(num-i-1)*a;
        if(ti<=T) return 1;
    }
    return 0;
}

int main(){
    scanf("%d%I64d%I64d%I64d",&n,&a,&b,&T);
    scanf("%s",s+1);
    sum[0]=0;
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='w');
    if((LL)sum[n]*b+(LL)(n-1)*a+n<=T) {printf("%d\n",n);return 0;}

    int L=0,R=n-1,M;

    while(L<=R){
        M=(L+R)>>1;
        if(check(M)) L=M+1;
        else R=M-1;
    }
    printf("%d\n",L-1);
    return 0;
}
