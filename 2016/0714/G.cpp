# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL L,eul;

LL Euler(LL x){
    LL ans=x,a=x;
    for(LL i=2;i*i<=x;i++){
        if(x%i==0) {ans/=i;while(x%i==0) x/=i;}
    }
    if(x>1) ans/=x;

    x=a;
    for(LL i=2;i*i<=x;i++){
        if(x%i==0) {ans*=(i-1);while(x%i==0) x/=i;}
    }
    if(x>1) ans*=(x-1);
    return ans;
}

LL fast_mul(LL a,LL b){
    LL res=0;
    while(b>0){
        if(b&1) res=(res+a);while(res>=L) res-=L;
        a=a+a;while(a>=L) a-=L;
        b>>=1;
    }
    return res;
}

LL fast_pow(LL a,LL b){
    LL c=a;a=1;
    while(b>0){
        if(b&1) a=fast_mul(a,c);
        c=fast_mul(c,c);
        b>>=1;
    }
    return a;
}

bool check(LL x){
    if(fast_pow(10,x)==1) return true;
    return false;
}

int main(){
    freopen("input.txt","r",stdin);
    int Tcase=0;
    while(scanf("%I64d",&L)!=EOF){
        if(!L) break;
        printf("Case %d: ",++Tcase);
        L=9*L;
        for(int i=1;i<=3;i++) if(L%2==0) L/=2;
        if(L%2==0||L%5==0) {puts("0");continue;}

        eul=Euler(L);

        LL ans=eul;
        for(LL i=1;i*i<=eul;i++){
            if(eul%i==0){
               // printf("i:%I64d %I64d\n",i,eul/i);
                if(check(i)) ans=min(ans,i);
                if(check(eul/i)) ans=min(ans,eul/i);
            }
        }

        printf("%I64d\n",ans);
    }
    return 0;
}
