#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000010;
typedef long long LL;
int n;
int first[maxn],next[maxn<<1],v[maxn<<1],w[maxn<<1],edge;
int q[maxn],head,tail;
int fa[maxn],size[maxn];
void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}
int main(){
	int a,b,c;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	head=tail=0;q[head]=1;fa[1]=0;
	while(head<=tail){
		int x=q[head++];
		//printf("x:%d\n",x);
		for(int e=first[x];e!=-1;e=next[e])
			if(v[e]!=fa[x])
				q[++tail]=v[e],fa[v[e]]=x;
	}
	LL ans=0;
	for(int i=tail;i>=0;i--){
		int x=q[i];
		//printf("x:%d\n",x);
		size[x]=1;
		for(int e=first[x];e!=-1;e=next[e])
			if(v[e]!=fa[x])
				size[x]+=size[v[e]],ans+=(LL)w[e]*abs(size[v[e]]-(n-size[v[e]]));
	}
	printf("%lld\n",ans);
	return 0;
}
/*
5
1 2 3
2 3 3
3 4 3
4 5 3

*/
