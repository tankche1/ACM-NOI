# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=10010;
const int mod=21092013;
int n;
int first[maxn],nnext[maxn<<1],v[maxn<<1];
int size[maxn],dp[maxn],w[maxn],edge=0,fa[maxn];
char c;
void read(int &a)
{
    a=0;
    c=getchar();
    for(;c<'0'||c>'9';c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        a=a*10+c-'0';
    return;
}

void add_edge(int a,int b,int c){
	nnext[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}
int num;

void dfs_size(int x){
	size[x]=1;
	for(int e=first[x];e!=-1;e=nnext[e])
		if(v[e]!=fa[x]) fa[v[e]]=x,dfs_size(v[e]),size[x]+=size[v[e]];
}

bool used[maxn];

int L[maxn],R[maxn];
LL ans[maxn];

void choose(int &x){
	int mx=0,son;
	for(int e=first[x];e!=-1;e=nnext[e]){
		if(!used[v[e]]&&size[v[e]]>mx)
			mx=size[v[e]],son=v[e];
	}
	if(mx>num/2){
		fa[x]=son;size[x]-=size[son];size[son]+=size[x];fa[son]=0;
		x=son;
		choose(x);
	}
}

void calc(x){

}

void solve(int x){
    num=size[x];
    if(num==1){
        for(int i=L[x];i<=R[x];i++) ans[i]++;
        return;
    }
    choose(x);
    ans+=calc(x);
    used[x]=1;
	for(int e=first[x];e!=-1;e=nnext[e]){
		if(!used[v[e]]) solve(v[e]);
	}
}

int main(){
    int tcase,a,b;
    read(tcase);
    while(tcase--){
        read(n);
        for(int i=1;i<n;i++)
            read(a),read(b),add_edge(a,b),add_edge(b,a);
        for(int i=1;i<=n;i++)
            scanf("%d",&L[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&R[i]);
        fa[1]=1;
        dfs_size(1);memset(used,false,sizeof(used));memset(ans,0,sizeof(ans));
        solve(1);
    }
    return 0;
}
