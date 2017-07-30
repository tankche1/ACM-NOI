# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxm=1000010;
int n,m;

int first[maxn],v[maxm*2],next[maxm*2],cnt=0;

void add_edge(int a,int b){
	next[cnt]=first[a];
	first[a]=cnt;
	v[cnt++]=b;
}

int num[maxn],label[maxn],rank[maxn];
void MCS(){
	memset(num,0,sizeof(num));
	memset(label,0,sizeof(label));
	for(int i=n;i>=1;i--){
		int maxnum=-1,k;
		for(int j=1;j<=n;j++) if((!label[j])&&num[j]>maxnum) {maxnum=num[j];k=j;}
		label[k]=i;
		for(int e=first[k];e!=-1;e=next[e]){
			num[v[e]]++;
		}
		rank[i]=k;
	}
}
int color[maxn];
bool vis[maxn];
int main(){
	scanf("%d%d",&n,&m);
	int a,b;
	memset(first,-1,sizeof(first));
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);add_edge(b,a);
	}
	MCS();int maxcol=0;
	memset(color,0,sizeof(color));
	for(int i=n;i>=1;i--){
		int x=rank[i];
		memset(vis,false,sizeof(vis));
		for(int e=first[x];e!=-1;e=next[e]){
			vis[color[v[e]]]=true;
		}
		for(int j=1;j<=n;j++)
			if(!vis[j]) {color[x]=j;maxcol=max(maxcol,j);break;}
	}
	printf("%d\n",maxcol);
	return 0;
}
