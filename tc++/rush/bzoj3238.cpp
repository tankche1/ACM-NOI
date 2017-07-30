#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=500010<<1;
inline int lowbit(int x) {return x&(-x);}
char s[maxn];
int n;
int pre[maxn],next[maxn];
int C[maxn];

int query_max(int x){
	int res=0;
	while(x) res=max(res,C[x]),x-=lowbit(x);
	return res;
}

void insert_max(int x,int val){
	while(x<=n) C[x]=max(C[x],val),x+=lowbit(x);
}

int query_min(int x){
	int res=n;
	while(x) res=min(res,C[x]),x-=lowbit(x);
	return res;
}

void insert_min(int x,int val){
	while(x<=n) C[x]=min(C[x],val),x+=lowbit(x);
}

int sa[maxn],t1[maxn],t2[maxn],c[maxn],height[maxn],rank[maxn];

void get_sa(int m){
	int *x=t1,*y=t2;
	for(int i=0;i<m;i++) c[i]=0;
	for(int i=0;i<n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<m;i++) c[i]+=c[i-1];
	for(int i=0;i<n;i++) sa[--c[x[i]]]=i;
	
	for(int k=1;;k<<=1){
		int p=0;
		for(int i=n-1;i+k>=n;i--) y[p++]=i;
		for(int i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
		
		for(int i=0;i<m;i++) c[i]=0;
		for(int i=0;i<n;i++) c[x[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];
			
		for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
			
		swap(x,y);
		x[sa[0]]=p=0;
		for(int i=1;i<n;i++)
			x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?p:++p;
		p++;
		if(p>=n) break;
		m=p;
	}
	//for(int i=0;i<n;i++)
		//printf("sa[%d]:%d\n",i,sa[i]);
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
	//for(int i=1;i<n;i++)
		//printf("height[%d]:%d\n",i,height[i]);
}
int same[maxn];

int main(){
	scanf("%s",s);
	n=strlen(s);
	get_sa('z'+1);
	get_height();
	memset(C,0,sizeof(C));
	for(int i=1;i<n;i++){
		pre[i]=query_max(height[i]+1);
		//printf("pre[%d]:%d\n",i,pre[i]);
		//if(height[pre[i]]==height[i]) same[i]=1;
		insert_max(height[i]+1,i);
	}
	for(int i=0;i<=n;i++) C[i]=n;
	for(int i=n-1;i>=1;i--){
		next[i]=query_min(height[i]+1-1);
		//printf("next[%d]:%d\n",i,next[i]);
		insert_min(height[i]+1,i);
	}
	long long ans=0;
	ans+=(long long)(n+1)*n/2*(n-1);
	for(int i=1;i<n;i++){
		if(same[i]) continue;
		ans-=(long long)(i-pre[i]+same[i])*(next[i]-i)*height[i]*2;
		//printf("%lld\n",(long long)(i-pre[i])*(next[i]-i)*height[i]*2);
	}
	printf("%lld\n",ans);
	return 0;
}
