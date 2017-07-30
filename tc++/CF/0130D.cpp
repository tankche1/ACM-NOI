#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=510;
const int maxm=1010;
const int INF=~0U>>1;
//vector<int> Face[maxn],Back[maxn];
int x[maxm],y[maxm];
int n,m;
int in[maxn],out[maxn];
int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		//Face[a].push_back(b);
		//Back[b].push_back(a);
		x[i]=a;y[i]=b;
	}
	int ans=INF;
	for(int c=1;c<=n;c++){
		int res=2*n-1;
	//	res+=n-Face[c].size();
	//	res+=n-Back[c].size();
		memset(in,0,sizeof(in));
		memset(out,0,sizeof(out));
		//printf("c:%d res:%d\n",c,res);
		int kk=0;
		for(int i=1;i<=m;i++){
			if(x[i]==c||y[i]==c) {kk++;continue;}
			if(in[y[i]]<1&&out[x[i]]<1) in[y[i]]++,out[x[i]]++;
			else res++;//printf("i:%d\n",i);
		}
		res-=kk;
		int need=0;
		//printf("res:%d\n",res);
		for(int i=1;i<=n;i++)
			if(i!=c) need+=2-in[i]-out[i];
		res+=need/2;
		//printf("%d %d\n",c,res);
		ans=min(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}
