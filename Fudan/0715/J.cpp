# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;

int n;
char s[maxn];

int sa[maxn],t1[maxn],t2[maxn],c[maxn],height[maxn],rrank[maxn];

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
	for(int i=0;i<n;i++) rrank[sa[i]]=i;
	int k=0;height[0]=0;
	for(int i=0;i<n;i++){
		if(k) k--;
		if(rrank[i]==0) continue;
		int j=sa[rrank[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[rrank[i]]=k;
	}
	//for(int i=1;i<n;i++)
		//printf("height[%d]:%d\n",i,height[i]);
}

LL count(int pos){//sa 0-pos个后缀提供的子串数目
	LL ret=0;int minx=n+10;
	for(int i=0;i<=pos;i++)
		ret+=n-sa[i];
	for(int i=pos+1;i<n;i++){
		minx=min(minx,height[i]);
		ret+=minx;
	}
	return ret;
}

LL count2(int x,int pos){//第x个后缀的前pos个字符提供多少子串
	LL ret=0;
	ret+=pos-height[x];
	int minx=pos-height[x];
	for(int i=x+1;i<n;i++){
		minx=min(minx,height[i]-height[x]);if(minx<=0) break;
		ret+=minx;
	}
	return ret;
}

void getans(int pos,int k){//第pos个后缀提供的第k个子串
	int L=height[pos]+1,R=n-sa[pos],M;
	while(L<=R){
		M=(L+R)>>1;
		if(count2(pos,M)<k) L=M+1;
		else R=M-1;
	}
	for(int i=sa[pos];i<=sa[pos]+L-1;i++) printf("%c",s[i]);puts("");
}

LL k;
int main(){
	int tcase,tnum=0;
	scanf("%d\n",&tcase);
	while(tcase--){
		scanf("%s%I64d",s,&k);
		n=strlen(s);
		get_sa('z'+1);
		get_height();
		
		int L=0,R=n-1,M;
		while(L<=R){
			M=(L+R)>>1;
			if(count(M)<k) L=M+1;
			else R=M-1;
		}
		if(L) k-=count(L-1);
		printf("Case %d: ",++tnum);
		getans(L,k);
	}
	return 0;
}
