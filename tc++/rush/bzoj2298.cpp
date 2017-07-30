#include<stdio.h>
#include<string.h>
# include<map>
#include<algorithm>
using namespace std;
const int maxn=100010;
typedef pair<int,int> pi;
map<pi,int> id;
int n;
int a[maxn],b[maxn];
int f[maxn];
int ans=0;
int cnt=0;

struct people{
	int l,r;
	people(int l=0,int r=0):l(l),r(r) {}
	bool operator == (const people &rhs){
		return l==rhs.l&&r==rhs.r;
	}
};
people p[maxn];

bool cmp(people A,people B){
	return A.r<B.r;
}

int main(){
	scanf("%d",&n);
	int m=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		if(a[i]+b[i]>n) ans++;
		else{
			p[++cnt]=people(a[i]+1,n-b[i]);
			if(!id.count(pi(p[cnt].l,p[cnt].r)))
				id[pi(p[cnt].l,p[cnt].r)]=1;
			else id[pi(p[cnt].l,p[cnt].r)]++;
			m=max(m,p[cnt].r);
		}
	}
	sort(p+1,p+cnt+1,cmp);
	cnt=unique(p+1,p+cnt+1)-p;
	f[0]=0;
	int now=1;
	for(int i=1;i<=m;i++){
		f[i]=f[i-1];
		while(p[now].r==i){
			f[i]=max(f[p[now].l-1]+min(id[pi(p[now].l,p[now].r)],p[now].r-p[now].l+1),f[i]);
			now++;
		}
	}
	printf("%d\n",n-f[m]);
	return 0;
}
