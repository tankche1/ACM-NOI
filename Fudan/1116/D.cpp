# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
const int mod=1000000007;
typedef long long LL;
int prime[100000],p_cnt=0;//p_cnt=78498
int n,a[maxn],q;

struct Query{
    int l,r,bh;
    Query() {}
    bool operator < (const Query &rhs)const{
        return l<rhs.l;
    }
}que[maxn];
bool vis[1000100];
void get_prime(){
    int j;
    memset(vis,false,sizeof(vis));
    for(int i=2;i<=1000000;i++){
            //printf("i:%d\n",i);
        if(vis[i]) continue;
        prime[++p_cnt]=i;
       // if(i<=100) printf("i:%d\n",i);
        j=i+i;
        while(j<=1000000){
            vis[j]=1;j+=i;
        }
    }
    //printf("p_cnt:%d\n",p_cnt);
}

int p[maxn][21],right[maxn][21];
int pos[1000010];
void anal_pri(int i){
    int x=a[i];
    p[i][0]=0;
    for(int j=1;prime[j]*prime[j]<=x;j++){
        if(x%prime[j]==0){

            p[i][++p[i][0]]=prime[j];//printf(" hei %d cnt:%d \n",prime[j],p[i][0]);
            while(x%prime[j]==0) x/=prime[j];
            right[i][p[i][0]]=pos[prime[j]];
            pos[prime[j]]=i;
        }
    }
    //printf("i:%d x:%d cnt:%d\n",i,x,p[i][0]);
    if(x!=1){
        p[i][++p[i][0]]=x;right[i][p[i][0]]=pos[x];pos[x]=i;x=1;
    }
    //printf("i:%d x:%d cnt:%d\n",i,x,p[i][0]);
    //for(int j=1;j<=p[i][0];j++)
     //   printf("pri:%d right:%d\n",p[i][j],right[i][j]);
}

LL fast_pow(LL a,LL b){
    if(b==0) return 1;
    LL half=fast_pow(a,b>>1);
    half=half*half%mod;
    if(b&1) half=half*a%mod;
    return half;
}
LL inverse(LL a){
    return fast_pow(a,mod-2);
}

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    int n;
    LL C[maxn];
    void init(int nn) {n=nn;for(int i=1;i<=n;i++) C[i]=1;}
    void mul(int x,int val){
        while(x<=n){C[x]=C[x]*val%mod;x+=lowbit(x);}
    }

    LL sum(int x){
        LL res=1;
        while(x>0){res=res*C[x]%mod;x-=lowbit(x);}
        return res;
    }
}fwt;
LL ans[maxn];

int main(){
    get_prime();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    memset(pos,-1,sizeof(pos));
    for(int i=n;i>=1;i--)
        anal_pri(i);
    fwt.init(n);
    for(int i=1;i<=n;i++){
        fwt.mul(i,a[i]);
    }
    for(int i=2;i<=1000000;i++){
        if(pos[i]!=-1)
            fwt.mul(pos[i],(LL)inverse(i)*(i-1)%mod);//,printf("i:%d p:%d\n",pos[i],i);
    }
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d",&que[i].l,&que[i].r);que[i].bh=i;
    }
    sort(que+1,que+q+1);
    int now=1;
    for(int i=1;i<=n;i++){
            //printf("i:%d\n",i);
        if(i!=1){
            fwt.mul(i-1,inverse(a[i-1]));
            for(int j=1;j<=p[i-1][0];j++){
                fwt.mul(i-1,inverse(p[i-1][j]-1)*p[i-1][j]%mod);
                if(right[i-1][j]!=-1) {
                        //printf("pri:%d right:%d\n",p[i-1][j],right[i-1][j]);
                    fwt.mul(right[i-1][j],inverse(p[i-1][j])*(p[i-1][j]-1)%mod);
                }
            }
        }
        while(now<=q&&que[now].l==i){
            ans[que[now].bh]=fwt.sum(que[now].r);
            now++;
        }
    }
    for(int i=1;i<=q;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
