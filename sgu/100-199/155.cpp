# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=50010;
int ch[maxn][2];int fa[maxn];
struct state{
	int key,val,bh;
	state(int key=0,int val=0):key(key),val(val) {}
	bool operator <(const state &rhs)const{
		return val<rhs.val;
	}
};
state node[maxn];
int n;
int S[maxn],top=0;

void dfs(int x,int fa){
	if(x==0) return;
	printf("%d %d %d\n",fa,ch[x][0],ch[x][1]);
	dfs(ch[x][0],x);dfs(ch[x][1],x);
}

int main(){
	scanf("%d",&n);
	memset(ch[0],0,sizeof(ch[0]));
	S[0]=0;
	node[0].bh=0;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&node[i].val,&node[i].key),node[i].bh=i;
	sort(node+1,node+n+1);//for(int i=1;i<=n;i++) printf("bh:%d key:%d value:%d\n",node[i].bh,node[i].key,node[i].val);
	for(int i=1;i<=n;i++){
		int L=1,R=top;
		while(L<=R){
			int M=(L+R)>>1;
			if(node[i].key>node[S[M]].key) L=M+1;
				else R=M-1;
		}
		L--;//printf("%d %d %d %d\n",node[S[L]].bh,node[i].bh,node[S[L+1]].bh,L==top);
		ch[node[S[L]].bh][1]=node[i].bh;fa[node[i].bh]=node[S[L]].bh;
		if(L!=top) ch[node[i].bh][0]=node[S[L+1]].bh,fa[node[S[L+1]].bh]=node[i].bh;
		top=L+1;S[top]=i;
	}
	puts("YES");
	for(int i=1;i<=n;i++)
		printf("%d %d %d\n",fa[i],ch[i][0],ch[i][1]);
	return 0;
}
