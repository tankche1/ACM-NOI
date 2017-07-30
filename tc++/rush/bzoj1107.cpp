#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=100010;
vector<int> ve[maxn][2];
int n,m,p,k;
int r[maxn],l[maxn];

inline int lowbit(int x) {return x&-x;}

struct FenwickTree{
	int C[maxn],n;
	void init(int nn){n=nn;memset(C,0,sizeof(C));}
	
	void Add(int x,int val){
		while(x<=n) C[x]=max(C[x],val),x+=lowbit(x);
	}
	
	int query(int x) {int ans=-maxn; while(x) ans=max(ans,C[x]),x-=lowbit(x);return ans;}
}fwt;

int calc(int k){
	int L=n;
	int ans=0;
	l[0]=maxn;
	for(int R=n;R>=1;R--){
		while(r[R]+l[L-1]<=k) L--;
		if(r[R]+l[L]<=k)
			ans=max(ans,R-L+1);
	}
	return ans;
}

int main(){
	int x,y,z;
	scanf("%d%d%d%d",&n,&m,&p,&k);
	for(int i=1;i<=p;i++){
		scanf("%d%d%d",&x,&y,&z);
		y=m-y+1;
		ve[x][z].push_back(y);
	}
	m++;
	r[1]=0;
	fwt.init(m+1);
	for(int i=1;i<n;i++){
		sort(ve[i][1].begin(),ve[i][1].end());
		for(int e=ve[i][1].size()-1;e>=0;e--) fwt.Add(ve[i][1][e],fwt.query(ve[i][1][e])+1);
		r[i+1]=i-fwt.query(m+1);
	}
	
	l[n]=0;
	fwt.init(m+1);
	for(int i=n-1;i>=1;i--){
		sort(ve[i][0].begin(),ve[i][0].end());
		for(int e=ve[i][0].size()-1;e>=0;e--) fwt.Add(ve[i][0][e],fwt.query(ve[i][0][e])+1);
		l[i]=n-i-fwt.query(m+1);
	}
	
	printf("%d\n",calc(k)-calc(0));
	return 0;
}
