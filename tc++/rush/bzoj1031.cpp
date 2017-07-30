# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;

char s[maxn];
int n;
int sa[maxn],t[maxn],t2[maxn],c[maxn];

void build_sa(int m){
	int *x=t,*y=t2;
	for(int i=0;i<m;i++) c[i]=0;
	for(int i=0;i<n;i++)  c[x[i]=s[i]]++;
	for(int i=1;i<m;i++) c[i]+=c[i-1];
	for(int i=0;i<n;i++) sa[--c[x[i]]]=i;
		
	for(int k=1;k<=n;k<<=1){
		int p=0;
		for(int i=n-k;i<n;i++) y[p++]=i;
		for(int i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
			
		for(int i=0;i<m;i++) c[i]=0;
		for(int i=0;i<n;i++)  c[x[i]]++;
		for(int i=1;i<m;i++) c[i]=c[i]+c[i-1];
		for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
			
		swap(x,y);
		p=1;x[sa[0]]=0;
		for(int i=1;i<n;i++)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
		if(p>=n) break;
		m=p;
	}
	//for(int i=0;i<n;i++) printf("%d\n",sa[i]);
}
char ans[maxn];

int main(){
	int m=0;
	scanf("%s",s);
	int nn=strlen(s);
	for(int i=nn;i<2*nn;i++)
	{s[i]=s[i-nn];if(s[i]>m) m=s[i];}
	n=nn*2;
	s[n]='\0';
	build_sa(m+1);
	int p=0;
	for(int i=0;i<n;i++){
		if(sa[i]<nn) ans[p++]=s[sa[i]+nn-1];
	}
	ans[p]='\0';
	puts(ans);
	return 0;
}
