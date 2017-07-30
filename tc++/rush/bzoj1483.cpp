#include<stdio.h>
#include<string.h>
#include<algorithm>
const int maxn=1000010;
using namespace std;
int n,m;
int col[maxn];
int first[maxn],next[maxn],num[maxn];
int ans;
int bh[maxn];//颜色i的bh 方便启发式合并
int main(){
	int op,x,y;
	scanf("%d%d",&n,&m);
	memset(num,0,sizeof(num));col[0]=-1;ans=0;
	memset(first,-1,sizeof(first));
	for(int i=1;i<=n;i++){
		scanf("%d",&col[i]),num[col[i]]++,next[i]=first[col[i]],first[col[i]]=i;
		if(col[i]!=col[i-1]) ans++;
	}
	for(int i=1;i<=maxn;i++) bh[i]=i;
		
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		if(op==2) printf("%d\n",ans);
		else{
			scanf("%d%d",&x,&y);if(x==y) continue;
			if(num[bh[x]]>num[bh[y]]) swap(bh[x],bh[y]);
			x=bh[x];y=bh[y];
			if(num[x]==0) continue;
			for(int e=first[x];e!=-1;e=next[e]){
				if(col[e]!=col[e-1]) ans--;
				if(e<n&&col[e]!=col[e+1]) ans--;
			}
			for(int e=first[x];e!=-1;e=next[e]) col[e]=y;
			int last;
			for(int e=first[x];e!=-1;e=next[e]){
				if(col[e]!=col[e-1]) ans++;
				if(e<n&&col[e]!=col[e+1]) ans++;
				last=e;
			}
			next[last]=first[y];first[y]=first[x];
			num[y]+=num[x];num[x]=0;first[x]=0;
		}
	}
	return 0;
}
