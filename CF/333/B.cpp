# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
const int INF=~0U>>1;
LL ans;
int n,q;
int h[maxn];
int x[maxn];
int l[maxn],r[maxn];

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",&h[i]);
    for(int i=1;i<n;i++)
        x[i]=abs(h[i]-h[i+1]);
    l[1]=0;x[0]=INF;
    n--;
    int S[maxn],S_top=-1;
    S[++S_top]=0;S[++S_top]=1;
    for(int i=2;i<=n;i++){
        while(x[i]>x[S[S_top]]) S_top--;
        l[i]=S[S_top];
        S[++S_top]=i;
        //printf("l[%d]:%d\n",i,l[i]);
    }

    r[n]=n+1;x[n+1]=INF;
    S_top=-1;
    S[++S_top]=n+1;S[++S_top]=n;
    for(int i=n-1;i>=1;i--){
        while(x[i]>=x[S[S_top]]) S_top--;
        r[i]=S[S_top];
        S[++S_top]=i;
        //printf("r[%d]:%d\n",i,r[i]);
    }
    n++;

    int L,R;
    for(int i=1;i<=q;i++){
        scanf("%d%d",&L,&R);ans=0;
        for(int j=L;j<R;j++){
                //printf("j:%d zuobian:%d youbian:%d  + %I64d\n",j,(j-max(l[j],L-1)),(min(r[j],R)-j),(LL)x[j]*(j-max(l[j],L-1))*(min(r[j],R)-j));
            ans+=(LL)x[j]*(j-max(l[j],L-1))*(min(r[j],R)-j);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
