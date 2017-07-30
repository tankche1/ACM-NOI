#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
const int N=100000;
const LL mod=(LL)1<<31;
int n,m,A,q;
LL G=0;

int f[maxn],miu[maxn];
bool vis[maxn];
int ans[maxn];

inline int lowbit(int x) {return x&(-x);}
struct Duty{
	int R,C,A,bh;
	Duty(int R=0,int C=0,int A=0):R(R),C(C),A(A) {}
	bool operator < (const Duty &rhs)const{
		return A<rhs.A;
	}
};
Duty ask[maxn];
typedef pair<int,int> pi;
pi p[maxn];int cnt=0;

LL C[maxn];
void add(int x,int val) {while(x<=N) C[x]+=val,x+=lowbit(x);}
LL sum(int x) {LL res=0;while(x) {if(C[x]>=mod) C[x]%=mod;res+=C[x],x-=lowbit(x);G=max(G,res);if(res>=mod) res%=mod;}return res;}

void getprime(){
	int x;
	for(int i=1;i<=N;i++) miu[i]=1,f[i]=1;p[cnt++]=pi(1,1);
	for(int i=2;i<=N;i++){
		if(!vis[i]){
			miu[i]=-1;
			for(int j=i*2;j<maxn;j+=i){
				vis[j]=1;
				miu[j]=-miu[j];
				if((j%(i*i))==0) miu[j]=0;
			}
		}
		for(int j=i;j<=N;j+=i)
			f[j]+=i;
		p[cnt++]=pi(f[i],i);
	}
	sort(p,p+cnt);
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	getprime();
	scanf("%d",&q);//printf("%d\n",q);
	for(int i=1;i<=q;i++)
		scanf("%d%d%d",&ask[i].R,&ask[i].C,&ask[i].A),ask[i].bh=i;//,printf("%d %d %d\n",ask[i].R,ask[i].C,ask[i].A);
	//return 0;
	sort(ask+1,ask+q+1);
	int last=0;
	for(int t=1;t<=q;t++){
		int n=ask[t].R,m=ask[t].C,T=1;
		for(int i=last;i<cnt&&p[i].first<=ask[t].A;i++){
			//if(p[i].second<=n) 
				//printf("i:%d f[%d]:%d\n",i,p[i].second,p[i].first);
			for(int j=p[i].second;j<=N;j+=p[i].second)
				add(j,f[p[i].second]*miu[j/p[i].second]);//printf("j:%d %d\n",j,f[i]*miu[j/i]);
			last=i+1;
		}
			LL res=0;
			while(T<=n&&T<=m){
				int nextt=min(n/(n/T),m/(m/T));//printf("T:%d nextt:%d\n",T,nextt);
				res=(res+(((LL)(n/T)*(m/T)%mod)*((sum(nextt)-sum(T-1))%mod)%mod))%mod;//printf("res:%lld\n",res);
				//printf("%lld %lld\n",((LL)(n/T)*(m/T)%mod),((sum(nextt)-sum(T-1))%mod));
				T=nextt;
				T++;
			}
			//printf("res:%lld\n",res%mod);
		ans[ask[t].bh]=res;
	}
	//printf("%lld\n",(mod-1)*(mod-1));
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]& 0x7fffffff);
		//printf("%lld\n",G);
	return 0;
}
