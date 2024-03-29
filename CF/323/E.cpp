# include<stdio.h>
# include<string.h>
# include<string>
# include<algorithm>
using namespace std;
typedef long long LL;
const int mod=1000000007;
inline int add(int a,int b){if(a+b>=mod) return a+b-mod;return a+b;}
inline void inc(int &a,int b) {a=add(a,b);}
inline int sub(int a,int b) {if(a-b<0) return a-b+mod;return a-b;}
inline void dec(int &a,int b) {a=sub(a,b);}
inline int mul(int a,int b) {return (int)((LL)a*b%mod);}

const int N=210;
const int V=4;
const int S=(1<<V);
const int M=(1<<S);
char s[N*3];
int dp[N][M];
int pos;

const string vars="ABCDabcd";
const string ops="|&";
int n=0;

int maskone(int v){
    int mask=0;
    for(int i=0;i<S;i++){
        if((i>>v)&1)
            mask|=(1<<i);
    }
    return mask;
}

int top[2][M];
int sl[M],sr[M],_s[M];

void getsum(int *a){
    for(int i=0;i<S;i++){
        for(int mask=0;mask<M;mask++){
            if(!((mask>>i)&1)) inc(a[mask^(1<<i)],a[mask]);
        }
    }
}

void door(int l,int r,int o){
    for(int i=0;i<M;i++) sl[i]=dp[l][i];
    for(int i=0;i<M;i++) sr[i]=dp[r][i];

    getsum(sl);getsum(sr);
    for(int mask=0;mask<M;mask++){
        _s[mask]=mul(sl[mask],sr[mask]);
    }

    for(int i=0;i<S;i++){
        for(int mask=0;mask<M;mask++)
            if(!((mask>>i)&1)) dec(_s[mask^(1<<i)],_s[mask]);
    }
    for(int mask=0;mask<M;mask++) top[o][mask]=_s[mask];
}

# define negate __negate
void negate(int *a){
    reverse(a,a+M);
}

int parse(){
    if(s[pos]!='('){
        int v=vars.find(s[pos++]);
        if(v==-1){
            for(int i=0;i<V;i++){
                dp[n][maskone(i)]=1;
                dp[n][(M-1)^maskone(i)]=1;
            }
        }
        else{
            if(v<V)
                dp[n][maskone(v)]=1;
            if(v>=V)
                dp[n][(M-1)^maskone(v-V)]=1;
        }
        return n++;
    }
    int me=n++;
    pos++;
    int l=parse();
    pos++;
    int op=ops.find(s[pos]);
    pos++;pos++;
    int r=parse();
    pos++;
    door(l,r,0);
    negate(dp[l]);negate(dp[r]);
    door(l,r,1);
    negate(top[1]);

    if(op==-1){
        for(int mask=0;mask<M;mask++){
            dp[me][mask]=add(top[0][mask],top[1][mask]);
        }
    }
    else
        for(int mask=0;mask<M;mask++)
            inc(dp[me][mask],top[op][mask]);
    return me;
}

int req[M];
int main(){
    scanf("%s",s);

    pos=0;
    int root=parse();

    int m,v;
    scanf("%d",&m);
    memset(req,-1,sizeof(req));
    for(int i=1;i<=m;i++){
        int mask=0;
        for(int j=0;j<V;j++){
            scanf("%d",&v);
            if(v) mask=mask^(1<<j);
        }
        scanf("%d",&req[mask]);
    }

    int ans=0;
    for(int mask=0;mask<M;mask++){
        bool good=true;
        for(int i=0;i<S;i++){
            if(req[i]==-1||req[i]==((mask>>i)&1)) good=true;
            else {good=false;break;}
        }
        if(good) inc(ans,dp[root][mask]);
    }
    printf("%d\n",ans);
    return 0;
}
