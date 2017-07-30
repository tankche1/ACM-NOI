# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=10;
int mod=1000000007;
typedef long long LL;
int n,m;
int out[1<<maxn];
LL expand[1<<maxn][1<<maxn];
LL connect[1<<maxn],biconnect[1<<maxn];
LL way[1<<maxn][1<<maxn];
LL h[1<<maxn];
LL two[maxn*maxn];

int digit[1<<maxn];
void prepare(){
    digit[0]=0;
    for(int i=1;i<1024;i++){
        digit[i]=digit[i>>1]+(i&1);
    }
    two[0]=1;
    for(int i=1;i<100;i++) two[i]=two[i-1]<<1,two[i]%=mod;
}

int main(){
    int Case,a,b;
    scanf("%d",&Case);
    prepare();
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++) out[1<<i]=(1<<n)-1;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&a,&b);a--;b--;
            if((out[1<<a]>>b)&1) out[1<<a]^=1<<b;
            if((out[1<<b]>>a)&1) out[1<<b]^=1<<a;
        }

        connect[0]=1;h[0]=0;
        for(int S=1;S<(1<<n);S++){

            int one=S&(-S);int sta=S^one;

            h[S]=h[sta]+digit[out[one]&sta];

            connect[S]=two[h[S]];
            for(int T1=sta;T1;T1=(T1-1)&sta){
                int T=S^T1;
                connect[S]=(connect[S]+mod-connect[T]*two[h[S^T]]%mod)%mod;
            }
            //printf("connect[%d]:%I64d\n",S,connect[S]);
        }

        for(int S=1;S<(1<<n);S++){
            for(int T=0;T<(1<<n);T++){
                if(S&T) continue;
                int one=S&(-S);
                way[S][T]=way[S^one][T]+digit[out[one]&T];
            }
        }

        for(int S=1;S<(1<<n);S++){
            expand[S][S]=1;
            for(int T=(S-1)&S;T;T=(T-1)&S){
                expand[T][S]=0;
                int T1=S^T;
                int one=T1&(-T1);int sta=T1^one;

                for(int T2=sta;;T2=(T2-1)&sta){
                    int T3=T2^one;
                    expand[T][S]=(expand[T][S]+expand[T][S^T3]*connect[T3]%mod*way[T][T3]%mod)%mod;
                    if(T2==0) break;
                }
                //printf("expand[%d][%d]:%I64d\n",T,S,expand[T][S]);
            }
        }

        for(int S=1;S<(1<<n);S++){
            biconnect[S]=connect[S];
            int one=S&(-S);int sta=S^one;

            for(int T1=sta;T1;T1=(T1-1)&sta){
                int T=S^T1;
                biconnect[S]=(biconnect[S]+mod-biconnect[T]*expand[T][S]%mod)%mod;
                //if(T1==0) break;
            }
            //printf("biconnect[%d]:%I64d\n",S,biconnect[S]);
        }

        printf("%I64d\n",biconnect[(1<<n)-1]);
    }
    return 0;
}
