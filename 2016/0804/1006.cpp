# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL INF=(LL)1<<60;
int A[maxn];
int n;
LL cnt[22][22];
LL res;
int a[22];
LL ans,ansx,tmp;

void dfs(int cur){
    if(cur>19){
        if(res<ans){
            ans=res;ansx=0;
            for(int i=19;i>=0;i--) ansx=(ansx<<1)+a[i];
            //if(ansx<10) printf("res:%I64d ansx:%I64d\n",res,ansx);
        }
        else if(res==ans){
            tmp=0;
            for(int i=19;i>=0;i--) tmp=(tmp<<1)+a[i];
            //if(tmp<10) printf("res:%I64d tmp:%I64d\n",res,tmp);
            if(tmp<ansx) ansx=tmp;
        }

        return;
    }

    LL now=res;
    for(int i=0;i<2;i++){
        res=now;
        a[cur]=i;
        res+=cnt[cur][cur];
        for(int j=cur-1;j>=0;j--){
            if(a[j]==a[cur]) res+=cnt[cur][j];
            else res-=cnt[cur][j];
        }

        dfs(cur+1);
    }
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&A[i]);
        }

        memset(cnt,0,sizeof(cnt));
        for(int i=1,k;i<n;i++){
            for(k=19;k>=0;k--){
                if(((A[i]>>k)&1)^((A[i+1]>>k)&1)){
                    cnt[k][k]+=(1<<k);
                    break;
                }
            }

            for(int l=k-1;l>=0;l--){
                if(!(((A[i]>>l)&1)^((A[i+1]>>l)&1))) continue;
                if(((A[i]>>l)&1)==((A[i]>>k)&1)){
                    cnt[k][l]+=(1<<l);
                }
                else
                    cnt[k][l]-=(1<<l);
            }
        }

        /*for(int i=19;i>=0;i--){
            for(int j=i;j>=0;j--){
                if(cnt[i][j]!=0){
                    printf("cnt[%d][%d]:%d\n",i,j,cnt[i][j]);
                }
            }
        }*/
        res=0;ans=INF;
        dfs(0);

        printf("%I64d %I64d\n",ansx,ans);
    }
    return 0;
}
