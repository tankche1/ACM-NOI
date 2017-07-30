#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=200010;
int n,q;
int cnt=0;
int h[maxn>>1];
int s[maxn<<1],num[maxn<<1],cnum,sum[maxn<<1];

struct Suffix{
	int n;
	int *s;
	int t1[maxn],t2[maxn],c[maxn];
	int sa[maxn],height[maxn],rank[maxn];
	
	void init(int *ss,int nn){
		s=ss;n=nn;
	}
	
	void build_sa(int m){
		int *x=t1,*y=t2;
		for(int i=0;i<m;i++) c[i]=0;
		for(int i=0;i<n;i++) c[x[i]=s[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];
		for(int i=0;i<n;i++) sa[--c[x[i]]]=i;
		for(int j=1;j<n;j<<=1){
			int p=0;
			for(int i=n-1;i+j>=n;i--) y[p++]=i;
			for(int i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
			
			for(int i=0;i<m;i++) c[i]=0;
			for(int i=0;i<n;i++) c[x[i]]++;
			for(int i=1;i<m;i++) c[i]+=c[i-1];
			
			for(int i=n-1;i>=0;i--)
				sa[--c[x[y[i]]]]=y[i];
			swap(x,y);
			x[sa[0]]=0;p=0;
			for(int i=1;i<n;i++)
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+j]==y[sa[i-1]+j])?p:++p;
			m=++p;
			if(m>=n) break;
		}
	}
	
	void getHeight(){
		for(int i=0;i<n;i++) rank[sa[i]]=i;
		int k=0;height[0]=0;
		for(int i=0;i<n;i++){
			if(k) k--;
			if(rank[i]==0) continue;
			int j=sa[rank[i]-1];
			while(i+k<cnt&&j+k<cnt&&s[i+k]==s[j+k]) k++;
			height[rank[i]]=k;
		}
		//		for(int i=0;i<n;i++) printf("%d",num[s[i]]);puts("");
		//for(int i=0;i<n;i++) printf("sa[%d]:%d height:%d \n",i,sa[i],height[i]);
	}
};
Suffix suf;
int dp[maxn][19];
const int Step=18;

void prepare(){
	for(int i=0;i<cnt;i++) dp[i][0]=suf.height[i];
	for(int j=1;j<=Step;j++){
		for(int i=0;i<cnt;i++)
			dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
	}
}

int RMQ(int l,int r){
	int j;
	for(j=Step;j>=0;j--) if((1<<j)<=(r-l+1)) break;
	return min(dp[l][j],dp[r-(1<<j)+1][j]);
}

struct Node{
	int size;
	Node *ch[2];
	Node() {}
};
Node *null,seq[maxn*80];int seq_cnt=0;
Node *root[maxn];
Node *New(){
	Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=null;o->size=0;return o;
}

void Add(Node* &x,Node* &y,int L,int R,int val){
	x->size=y->size+1;
	if(L==R) return;
	int M=(L+R)>>1;
	if(val<=M) x->ch[1]=y->ch[1],x->ch[0]=New(),Add(x->ch[0],y->ch[0],L,M,val);
	else x->ch[0]=y->ch[0],x->ch[1]=New(),Add(x->ch[1],y->ch[1],M+1,R,val);
}

int query(Node* &x,int L,int R,int qL,int qR){
	if((qL<=L&&qR>=R)||x->size==0) return x->size;
	int M=(L+R)>>1,ans=0;
	if(qL<=M) ans+=query(x->ch[0],L,M,qL,qR);
	if(qR>M) ans+=query(x->ch[1],M+1,R,qL,qR);
	return ans;
}

int Query(int l,int r){
	l++;
	l--;r--;l--;r--;
	int L,R,qL,qR;
	L=0,R=suf.rank[l+n]-1;
	while(L<=R){
		int M=(L+R)>>1;
		if(RMQ(M+1,suf.rank[l+n])>=r-l+1) R=M-1;
		else L=M+1;
	}
	qL=R+1;
	L=suf.rank[l+n]+1,R=cnt-1;
	while(L<=R){
		int M=(L+R)>>1;
		if(RMQ(suf.rank[l+n]+1,M)>=r-l+1) L=M+1;
		else R=M-1;
	}
	qR=L-1;
	int ans=sum[qR];
	if(qL-1>=0) ans-=sum[qL-1];
	//printf("qL:%d qR:%d ans:%d pos:%d\n",qL,qR,ans,suf.rank[l+n]);
	if(l>1) ans+=query(root[l-2],0,cnt-1,qL,qR);
	ans=ans-query(root[r+1<=n-2?r+1:n-2],0,cnt-1,qL,qR);
	return ans;
}

int main(){
	null=new Node();null->ch[0]=null->ch[1]=null;null->size=0;
	int l,r;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	h[0]=h[1];
	cnt=0;
	for(int i=2;i<=n;i++){
		s[cnt++]=h[i]-h[i-1];
	}
	s[cnt++]=-2000000001;
	for(int i=2;i<=n;i++){
		s[cnt++]=h[i-1]-h[i];
	}
	//s[cnt++]=-1000000001;
	cnum=0;
	for(int i=0;i<cnt;i++)
		num[cnum++]=s[i];
	sort(num,num+cnum);
	cnum=unique(num,num+cnum)-num;
	for(int i=0;i<cnt;i++)
		s[i]=lower_bound(num,num+cnum,s[i])-num;
	suf.init(s,cnt);
	suf.build_sa(cnt);
	suf.getHeight();
	prepare();
	memset(sum,0,sizeof(sum));
	for(int i=0;i<n-1;i++) sum[suf.rank[i]]++;
	for(int i=1;i<cnt;i++) sum[i]+=sum[i-1];
	//for(int i=0;i<cnt;i++) printf("sum[%d]:%d\n",i,sum[i]);
	
	for(int i=0;i<n-1;i++){
		root[i]=New();Node *last=i==0?null:root[i-1];
		Add(root[i],last,0,cnt-1,suf.rank[i]);
	}
	
	scanf("%d",&q);
	for(int t=1;t<=q;t++){
		scanf("%d%d",&l,&r);
		if(l==r) printf("%d\n",n-1);
		else{
			printf("%d\n",Query(l,r));
		}
	}
	return 0;
}
