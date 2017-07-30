#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=500010;
const int maxm=500010;
const int maxs=500010;
const int Step=20;
int n,m;
int s[maxs];
int cnt=0;
int belong[maxs];
int lens[maxm],start[maxm];
int num[maxn],A[maxs];
int qL,qR;
int rangeL[maxm],rangeR[maxm];
int ans[maxm];
int dp[maxs][Step+1];
int last[maxs],next[maxs];
int bh[maxm];

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
	int n,C[maxs];
	void init(int nn){
		memset(C,0,sizeof(C));n=nn;
	}
	
	void Add(int x,int val){
		while(x<=n){
			C[x]+=val;x+=lowbit(x);
		}
	}
	
	int sum(int x){
		int res=0;
		while(x>0) res+=C[x],x-=lowbit(x);
		return res;
	}
}fwt;

struct Suffix{
	int sa[maxs],rank[maxs],height[maxs];
	int t1[maxs],t2[maxs],c[maxs];
	int n;int *s;
	
	void init(int *ss,int nn){
		s=ss;n=nn;
	}
	
	void build_sa(int m){
		int *x=t1,*y=t2;
		for(int i=0;i<m;i++) c[i]=0;
		for(int i=0;i<n;i++) c[x[i]=s[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];
		for(int i=0;i<n;i++) sa[--c[x[i]]]=i;
		
		for(int j=1;;j<<=1){
			int p=0;
			for(int i=n-1;i+j>=n;i--) y[p++]=i;
			for(int i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
			
			for(int i=0;i<m;i++) c[i]=0;
			for(int i=0;i<n;i++) c[x[i]]++;
			for(int i=1;i<m;i++) c[i]+=c[i-1];
			for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
			
			p=0;swap(x,y);x[sa[0]]=0;
			for(int i=1;i<n;i++)
				x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+j]==y[sa[i]+j])?p:++p;
			m=p+1;
			if(m>=n) break;
		}
		//for(int i=0;i<cnt;i++) printf("sa[%d]:%d\n",i,sa[i]);
	}
	
	void get_height(){
		for(int i=0;i<n;i++) rank[sa[i]]=i;
		int k=0;
		for(int i=0;i<n;i++){
			if(k) k--;
			if(rank[i]==0) continue;
			int j=sa[rank[i]-1];
			while(s[i+k]==s[j+k]) k++;
			height[rank[i]]=k;
		}
	}
}suf;

void prepare(){
	for(int i=1;i<cnt;i++)
		dp[i][0]=suf.height[i];
	for(int j=1;j<=Step;j++)
		for(int i=1;i<cnt;i++){
			if(i+(1<<(j-1))>=cnt) dp[i][j]=dp[i][j-1];
			else dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
		}
}

int RMQ(int L,int R){
	int j;
	for(j=Step;j>=0;j--)
		if(R-L+1>=(1<<j)) break;
	return min(dp[L][j],dp[R-(1<<j)+1][j]);
}

void get_range(int pos,int len){
	int L,R;
	L=0,R=pos-1;
	while(L<=R){
		int M=(L+R)>>1;
		if(RMQ(M+1,pos)>=len) R=M-1;
		else L=M+1;
	}
	qL=R+1;
	L=pos+1,R=cnt-1;
	while(L<=R){
		int M=(L+R)>>1;
		if(RMQ(pos+1,M)>=len) L=M+1;
			else R=M-1;
	}
	qR=L-1;
}

bool cmp1(int a,int b){
	return rangeL[a]<rangeL[b];
}

bool cmp2(int a,int b){
	return rangeR[a]<rangeR[b];
}

int main(){
	//freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	int x,len;
	int N=10001;
	scanf("%d%d",&n,&m);int nn=n;
	for(int i=1;i<=n;i++){
		scanf("%d",&len);
		for(int j=1;j<=len;j++)
			scanf("%d",&x),s[cnt++]=x,belong[cnt-1]=i;
		s[cnt++]=++N;belong[cnt-1]=-1;
		scanf("%d",&len);
		for(int j=1;j<=len;j++)
			scanf("%d",&x),s[cnt++]=x,belong[cnt-1]=i;
		s[cnt++]=++N;belong[cnt-1]=-1;
	}
	for(int i=1;i<=m;i++){
		start[i]=cnt;
		scanf("%d",&lens[i]);
		for(int j=1;j<=lens[i];j++)
			scanf("%d",&x),s[cnt++]=x,belong[cnt-1]=-1;
		s[cnt++]=++N;belong[cnt-1]=-1;
	}
	//puts("hey");
	//for(int i=0;i<cnt;i++) printf("%d ",s[i]);puts("");
	suf.init(s,cnt);
	suf.build_sa(N+1);
	suf.get_height();
	prepare();
	//puts("fuck");
	//for(int i=0;i<cnt;i++) printf("sa[%d]:%d\n",i,suf.sa[i]);
	
	for(int i=0;i<cnt;i++)
		A[suf.rank[i]+1]=belong[i];
	//for(int i=1;i<=cnt;i++) printf("A[%d]:%d\n",i,A[i]);
	
	for(int i=1;i<=m;i++){
		get_range(suf.rank[start[i]],lens[i]);
		rangeL[i]=qL+1,rangeR[i]=qR+1;
		//printf("%d %d\n",qL+1,qR+1);
	}
	
//	puts("go");
//	return 0;
	int n=++cnt;
	fwt.init(n);
	for(int i=1;i<=m;i++) bh[i]=i;
	sort(bh+1,bh+m+1,cmp1);
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++){
		if(A[i]==-1) continue;
		if(num[A[i]]==0) fwt.Add(i,1);num[A[i]]=1;
	}
	for(int i=1;i<=n;i++) num[i]=n+1;
	for(int i=n;i>=1;i--){
		if(A[i]==-1) continue;
		next[i]=num[A[i]],num[A[i]]=i;
	}
	
	int pre=1;
	for(int i=1;i<=m;i++){
		//printf("i:%d\n",i);
		int t=bh[i];
		for(int j=pre;j<rangeL[t];j++){
			if(A[j]==-1) continue;
			if(next[j]!=n+1) fwt.Add(next[j],1);
		}
		ans[t]=fwt.sum(rangeR[t])-fwt.sum(rangeL[t]-1);
		pre=rangeL[t];
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	
	memset(ans,0,sizeof(ans));
	fwt.init(n);
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++){
		if(A[i]==-1) continue;last[i]=num[A[i]],num[A[i]]=i;
	}
	
	for(int i=1;i<=m;i++) bh[i]=i;
	sort(bh+1,bh+m+1,cmp2);
	bh[0]=m+1;rangeR[m+1]=0;rangeL[m+1]=1;
	for(int i=m;i>=0;i--){
		//printf("%d\n",i);
		if(i!=m) {for(int j=rangeR[bh[i+1]];j>rangeR[bh[i]];j--) {if(A[j]==-1) continue;ans[A[j]]+=fwt.sum(j)-fwt.sum(last[j]);}}
		fwt.Add(rangeL[bh[i]],1);
	}
	for(int i=1;i<nn;i++) printf("%d ",ans[i]);printf("%d\n",ans[nn]);
	return 0;
}
