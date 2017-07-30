#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
typedef pair<int,int> pi;
typedef long long LL;
LL maxret=1e+18;
LL lim=maxret+10;
int n,L,P;
int len[maxn];
char s[40];
LL dp[maxn];
int sum[maxn];
struct state{
	int l,r,ch;
	state(int l=0,int r=0,int ch=0):l(l),r(r),ch(ch) {}
};
double fast_pow(double a,int b){
	if(b==0) return 1;
	double ans=fast_pow(a,b>>1);
	if(b&1) ans=ans*ans*a;
		else ans=ans*ans;
	return ans;
}

double D_abs(double a){
	if(a>=0) return a;
		return -a;
}

double CalcDP(int i,int j){
	return (double)dp[j]+fast_pow(D_abs((double)sum[i]-sum[j]-L),P);
}

bool Better(int a,int b,int c){
	return CalcDP(c,a)<=CalcDP(c,b);
}

int Binary_Search(state q,int i){
	int L=q.l,R=q.r;
	while(L<=R){
		int M=(L+R)>>1;
		if(Better(q.ch,i,M)) L=M+1;
			else R=M-1;
	}
	return L-1;
}

void Init(){
	scanf("%d %d %d\n",&n,&L,&P);L++;
	sum[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%s",s),len[i]=strlen(s),sum[i]=sum[i-1]+len[i]+1;
}

state q[maxn];

void solve(){
	dp[0]=0;
	int head=0,tail=-1;
	q[++tail]=state(1,n,0);
	for(int i=1;i<=n;i++){
		q[head].l=i;
		if(q[head].l>q[head].r) head++;
		double ret=CalcDP(i,q[head].ch);
		if(ret>lim)
			dp[i]=lim;
		else dp[i]=LL(ret);
		while(tail>=head&&Better(i,q[tail].ch,q[tail].l))
			tail--;
		if(tail<head) q[++tail]=state(i,n,i);
		else{
			int split=Binary_Search(q[tail],i);
			q[tail].r=split;
			if(split+1<=n)
				q[++tail]=state(split+1,n,i);
		}
	}
	if(dp[n]>maxret) 
		puts("Too hard to arrange");
	else printf("%lld\n",dp[n]);
		puts("--------------------");
}

int main(){
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		Init();
		solve();
	}
	return 0;
}
