#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=300010;
vector<int> Face[maxn],Back[maxn];
int n,p;
int in[maxn],C[maxn];

inline int lowbit(int x){ return x&(-x);}

void add(int x,int val){if(x==0) return;while(x<=n+1) C[x]+=val,x+=lowbit(x);}

int sum(int x){int res=0;while(x>0) res+=C[x],x-=lowbit(x);return res;}
int main(){
	int a,b;
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);in[a]++;in[b]++;
		Face[i].push_back(a);Face[i].push_back(b);
		Back[a].push_back(i);Back[b].push_back(i);
	}
	int ans=0;
	for(int i=1;i<=n;i++) add(in[i]+1,1);
	LL res=0;
	for(int i=1;i<=n;i++){
		for(int e=0;e<Back[i].size();e++){
			int v=Back[i][e];
			for(int d=0;d<2;d++)
				if(Face[v][d]!=i){
					add(in[Face[v][d]]+1,-1);in[Face[v][d]]--;add(in[Face[v][d]]+1,1);
				}
		}
		
		add(in[i]+1,-1);
		//for(int i=1;i<=4;i++) printf("in[%d]:%d\n",i,in[i]);
		ans=sum(n+1)-sum(p-in[i]-1+1);
		add(in[i]+1,1);
		
		for(int e=0;e<Back[i].size();e++){
			int v=Back[i][e];
			for(int d=0;d<2;d++)
				if(Face[v][d]!=i){
					add(in[Face[v][d]]+1,-1);in[Face[v][d]]++;add(in[Face[v][d]]+1,1);
				}
		}
		//printf("i:%d ans:%d\n",i,ans);
		res+=ans;
	}
	printf("%lld\n",res>>1);
	return 0;
}
