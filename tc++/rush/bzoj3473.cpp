#include<stdio.h>
#include<string.h>
# include<set>
#include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long LL;
int n,k;
int cnt=0;
int bh=1000;
char word[maxn>>1];
int s[maxn];
int org[maxn],length[maxn>>1];
LL ans[maxn>>1];
int got[maxn];//got[i]-i 有k个字符串的后缀
int dp[maxn][18];
const int Step=17;

struct Suffix{
	int *s;
	int n,m;
	int sa[maxn],t[maxn],t2[maxn],c[maxn];
	int rank[maxn],height[maxn];
	
	void init(int *t,int nn) {s=t;n=nn;}
	
	void build_sa(int m){
		int *x=t,*y=t2;
		for(int i=0;i<m;i++) c[i]=0;
		for(int i=0;i<n;i++) c[x[i]=s[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];
		
		for(int i=0;i<n;i++) sa[--c[x[i]]]=i;
		
		for(int k=1;k<n;k<<=1){
			int p=0;
			for(int i=n-1;i+k>=n;i--) y[p++]=i;
			for(int i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
			
			for(int i=0;i<m;i++) c[i]=0;
			for(int i=0;i<n;i++) c[x[i]]++;
			for(int i=1;i<m;i++) c[i]+=c[i-1];
				
			for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
			
			swap(x,y);
			p=0;x[sa[0]]=0;
			for(int i=1;i<n;i++)
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i-1]+k]==y[sa[i]+k])?p:++p;
			if(++p>=n) break;
			m=p;
		}
	}
	
	void getHeight(){
		int k=0;height[0]=0;
		for(int i=0;i<n;i++) rank[sa[i]]=i;
		for(int i=0;i<n;i++){
			if(k) k--;
			if(rank[i]==0) continue;
			int j=sa[rank[i]-1];
			while(s[i+k]==s[j+k]) k++;
			height[rank[i]]=k;
		}
	}
	
};
Suffix  suf;
set<int> ss;
int num[maxn];

void Insert(int x){
	if(num[x]==0) ss.insert(x);
	num[x]++;
}

void Erase(int x){
	if(num[x]==1) ss.erase(x);
	num[x]--;
}

void calc_got(){
	memset(num,0,sizeof(num));
	for(int i=0;i<cnt;i++){
		if(org[suf.sa[i]]==-1) {got[i]=i==0?-1:got[i-1];continue;}
		Insert(org[suf.sa[i]]);
		if(ss.size()<k) got[i]=-1;
		else{
			int l=got[i-1]==-1?0:got[i-1];
			while(org[suf.sa[l]]==-1||num[org[suf.sa[l]]]>1||ss.size()>k) {if(org[suf.sa[l]]!=-1) Erase(org[suf.sa[l]]);l++;}
			got[i]=l;
		}
	}
}

void prepare(){
	for(int i=1;i<cnt;i++)
		dp[i][0]=suf.height[i];
	for(int j=1;j<Step;j++){
		for(int i=1;i<cnt;i++){
			if(i+(1<<(j-1))<cnt) dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
			else dp[i][j]=dp[i][j-1];
		}
	}
}

int RMQ(int L,int R){
	int len=R-L+1,j;
	for(j=Step;j>=0;j--)
		if((1<<j)<=len) break;
	return min(dp[L][j],dp[R-(1<<j)+1][j]);
}

bool check(int x,int len){
	int L=0,R=suf.rank[x]-1,l,r;
	while(L<=R){
		int M=(L+R)>>1;
		if(RMQ(M+1,suf.rank[x])>=len) R=M-1;
		else L=M+1;
	}
	l=R+1;
	L=suf.rank[x]+1,R=cnt-1;
	while(L<=R){
		int M=(L+R)>>1;
		if(RMQ(suf.rank[x]+1,M)>=len) L=M+1;
		else R=M-1;
	}
	r=L-1;
	if(got[r]>=l) return true;
	else return false;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%s",word);
		int len=strlen(word);
		length[i]=len;
		for(int j=0;j<len;j++)
			s[cnt]=word[j],org[cnt++]=i;
		s[cnt]=bh++;org[cnt++]=-1;
	}
	s[cnt-1]=1;
	suf.init(s,cnt);
	suf.build_sa(bh);
	suf.getHeight();
	prepare();
	calc_got();
	
	memset(ans,0,sizeof(ans));
	for(int i=0;i<cnt;i++){
		if(org[i]==-1) continue;
		int L=1,R=length[org[i]];
		while(L<=R){
			int M=(L+R)>>1;
			if(check(i,M)) L=M+1;
			else R=M-1;
		}
		ans[org[i]]+=L-1;
	}
	for(int i=1;i<=n;i++){
		if(k==1) ans[i]=(LL)(length[i]+1)*length[i]/2;
		printf("%lld ",ans[i]);
	}puts("");
	return 0;
}
