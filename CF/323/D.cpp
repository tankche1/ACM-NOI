# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=3400;
const int mod=1000000007;
int dp[maxn][maxn][2][2];
int p,alpha;
vector<int> a,b,c;
char s[1010];

int Div(vector<int> &a,LL p,vector<int> &b){
    LL res=0;
    b.clear();
    for(int i=0;i<a.size();i++){
        res=res*10+a[i];
        if(b.size()>0||res>=p) b.push_back(res/p),res%=p;
    }
    return res;
}

int mul(int a,int b) {return (int)((LL)a*b%mod);}
void inc(int &a,int b){a+=b;if(a>=mod) a-=mod;}

int calc(int rm,int nrm){
    if(rm==1&&nrm==1) return ((LL)(1+p)*p/2)%mod;
    if(rm==1&&nrm==0) return ((LL)p*(p-1)/2)%mod;
    if(rm==0&&nrm==1) return ((LL)p*(p-1)/2)%mod;
    if(rm==0&&nrm==0) return ((LL)(1+p)*p/2)%mod;
}

int sum(int x){
    int ci=x+1-p;
    LL res=0;
    if(x>=p){
        res+=(LL)(ci+1)*p;res+=(LL)(ci+p)*(p-ci-1)/2;
    }
    else{
        res+=(LL)(x+2)*(x+1)/2;
    }
    res%=mod;
    return (int)res;
}

int main(){
    scanf("%d%d",&p,&alpha);
    scanf("%s",s);
    a.resize(strlen(s));
    for(int i=0;i<a.size();i++){
        a[i]=s[i]-'0';
    }

    while(a.size()){
        c.push_back(Div(a,p,b));
        a=b;
    }

    int npw;int t;
    reverse(c.begin(),c.end());
    dp[0][0][1][0]=1;
    int n=c.size();
    if (alpha > c.size()) { puts("0"); return 0; }
    //for(int i=0;i<n;i++) printf("%d",c[i]);puts("");
    for(int i=0;i<=n;i++){
        for(int pw=0;pw<=i&&pw<=alpha;pw++){
            for(int eq=0;eq<2;eq++){
                for(int rm=0;rm<2;rm++){
                    if(dp[i][pw][eq][rm]==0) continue;
                    //printf("dp[%d][%d][%d][%d]:%d\n",i,pw,eq,rm,dp[i][pw][eq][rm]);
                    if(i==n) continue;
                    int cur=dp[i][pw][eq][rm];
                    if(eq==0){
                        for(int nrm=0;nrm<2;nrm++){
                            npw=min(alpha,pw+nrm);
                            t=calc(rm,nrm);
                            inc(dp[i+1][npw][eq][nrm],mul(cur,t));
                            //printf("dp[%d][%d][%d][%d]:%d goto dp[%d][%d][%d][%d]:%d by %d\n",i,pw,eq,rm,dp[i][pw][eq][rm],i+1,npw,eq,nrm,dp[i+1][npw][eq][nrm],mul(cur,t));
                        }
                    }
                    else if(eq==1){
                        for(int nrm=0;nrm<2;nrm++){
                            npw=min(alpha,pw+nrm);
                            if(rm==0&&nrm==1) t=((LL)c[i]*(c[i]-1)/2)%mod;
                            if(rm==0&&nrm==0) t=((LL)c[i]*(c[i]+1)/2)%mod;
                            if(rm==1&&nrm==1) t=sum(p+c[i]-2)-sum(p-2);
                            if(rm==1&&nrm==0) t=sum(p+c[i]-1)-sum(p-1);
                            if(t<0) t+=mod;
                            //printf("t:%I64d\n",t);
                            inc(dp[i+1][npw][0][nrm],mul(cur,t));
                            //printf("dp[%d][%d][%d][%d]:%d goto dp[%d][%d][%d][%d]:%d by %d\n",i,pw,eq,rm,dp[i][pw][eq][rm],i+1,npw,0,nrm,dp[i+1][npw][0][nrm],mul(cur,t));

                            if(rm==0&&nrm==1) t=c[i];
                            if(rm==0&&nrm==0) t=c[i]+1;
                            if(rm==1&&nrm==1) t=p-c[i];
                            if(rm==1&&nrm==0) t=p-c[i]-1;
                            inc(dp[i+1][npw][1][nrm],mul(cur,t));
                            //printf("dp[%d][%d][%d][%d]:%d goto dp[%d][%d][%d][%d]:%d by %d\n",i,pw,eq,rm,dp[i][pw][eq][rm],i+1,npw,1,nrm,dp[i+1][npw][1][nrm],mul(cur,t));
                        }
                    }
                }
            }
        }
    }
    int ans=0;
    inc(ans,dp[n][alpha][0][0]);inc(ans,dp[n][alpha][1][0]);
    printf("%d\n",ans);
    return 0;
}
