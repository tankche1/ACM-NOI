# include<stdio.h>
# include<string.h>
# include<stack>
# include<algorithm>
using namespace std;
const int maxn=50010;
typedef long long LL;

struct Line{
	int k,b,bh;
	bool operator < (const Line &rhs)const{
		return k<rhs.k||(k==rhs.k&&b>rhs.b);
	}
	
	bool operator == (const Line &rhs)const{
		return k==rhs.k;
	}
};
Line line[maxn];
int n,nn;
stack<Line> S;
bool vis[maxn];

void solve(){
	//if(n<=2) {printf("%d\n",n);return;}
	//S.push(line[1]);S.push(line[2]);
	for(int i=1;i<=n;i++){
		while(S.size()>=2){
		Line top1=S.top();S.pop();Line top2=S.top();
		LL ans=(LL)(top1.b-top2.b)*(top1.k-line[i].k)-(LL)(line[i].b-top1.b)*(top2.k-top1.k);
		if(ans>=0){}
		else {S.push(top1);break;}
		}
		S.push(line[i]);
	}
	memset(vis,false,sizeof(vis));
	while(!S.empty()){
		vis[S.top().bh]=true;S.pop();
	}
	for(int i=1;i<=nn;i++)
		if(vis[i]) printf("%d ",i);
			printf("\n");
}

int main(){
//	freopen("input.txt","r",stdin);
	scanf("%d",&n);nn=n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&line[i].k,&line[i].b);line[i].bh=i;}
	sort(line+1,line+n+1);
	n=unique(line+1,line+n+1)-line-1;
	//for(int i=1;i<=n;i++) printf("%d %d\n",line[i].k,line[i].b);
	solve();
	return 0;
}
/*
*/
