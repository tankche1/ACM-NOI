# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=20;
int n,m;
int go[1<<maxn];
int u[410],v[410];
bool can[1<<maxn];
int sum[1<<maxn],all;

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        memset(go,0,sizeof(go));
        memset(can,0,sizeof(can));
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u[i],&v[i]);
            go[u[i]]|=(1<<v[i]);
            go[v[i]]|=(1<<u[i]);
        }

        can[0]=1;
        for(int i=0;i<n;i++) can[1<<i]=1;
        for(int i=0;i<(1<<n);i++){
            if(can[i]){
                for(int j=0;j<n;j++){
                    if(((i&(1<<j))==0)&&(i&go[j])){
                        can[i^(1<<j)]=1;
                    }
                }
            }
        }

        memset(sum,0,sizeof(sum));
        all=0;
        for(int i=0;i<(1<<n);i++){
            if(can[i]&&can[((1<<n)-1)^i]) {sum[i]++,all++;//printf("i:%d\n",i);
            }
        }

        all>>=1;

        for(int j=0;j<n;j++){
            for(int i=(1<<n)-1;i>=0;i--){
                if((i>>j)&1){
                    sum[i^(1<<j)]+=sum[i];
                }
                //if(!(i>>j&1)) sum[i]+=sum[i^(1<<j)];
            }
        }

        printf("Case #%d:",Tcase);
        for(int i=1;i<=m;i++){
            printf(" %d",all-sum[(1<<u[i])|(1<<v[i])]);
        }puts("");
    }
    return 0;
}
