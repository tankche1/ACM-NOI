# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=30010<<1;
struct suffix{
	char s[maxn];
	int sa[maxn],t[maxn],t2[maxn],c[maxn],n;
	int rank[maxn];
	
	void build_sa(int m){
		int *x=t,*y=t2;
	//	memset(c,0,sizeof(c));
		for(int i=0;i<m;i++) c[i]=0;
		for(int i=0;i<n;i++) c[x[i]=s[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];
		for(int i=0;i<n;i++)
			sa[--c[x[i]]]=i;
		for(int k=1;k<=n;k<<=1){
			//for(int i=0;i<n;i++) printf("sa[%d]:%d\n",i,sa[i]);
			int p=0;
			for(int i=n-1;i+k>=n;i--) y[p++]=i;
			for(int i=0;i<n;i++)
				if(sa[i]>=k) y[p++]=sa[i]-k;
			for(int i=0;i<m;i++) c[i]=0;
			for(int i=0;i<n;i++) c[x[i]]++;
			for(int i=1;i<m;i++) c[i]+=c[i-1];
			for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
				
			swap(x,y);
			p=1;x[sa[0]]=0;
			for(int i=1;i<n;i++)
				x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
			if(p>=n) break;
			m=p;
		}
		//for(int i=0;i<n;i++) printf("%c",s[i]);puts("");
		for(int i=0;i<n;i++)
			rank[sa[i]]=i;//printf("sa[%d]:%d\n",i,sa[i]);
	}
	
};
suffix suf1,suf2;
char ans[maxn];int cnt=0,n;
char s[maxn];
int main(){
	scanf("%d",&n);
	char t;
	for(int i=1;i<=n;i++){
	while((t=getchar())&&(t<'A'||t>'Z'));
		s[i-1]=t;
	}
	for(int i=0;i<n;i++)
		suf1.s[i]=s[i],suf1.s[n+n-1-i+1]=s[i];
	suf1.s[n]='A'-3;
	suf1.n=2*n+1;
	suf1.s[suf1.n++]='A'-5;
	suf1.build_sa('Z'+1);
	//suf2.build_sa('Z'+1);
	int left=0,right=n-1;
	while(left<right){
		if(s[left]<s[right]) ans[cnt++]=s[left++];
			else if(s[left]>s[right]) ans[cnt++]=s[right--];
				else{
					if(suf1.rank[left]<suf1.rank[n+n-1-right+1])  ans[cnt++]=s[left++];
						else ans[cnt++]=s[right--];
				}
	}
	ans[cnt++]=s[left];ans[cnt]='\0';
	for(int i=0;i<cnt;i++){
		printf("%c",ans[i]);if((i+1)%80==0) puts("");
	}
	return 0;
}
