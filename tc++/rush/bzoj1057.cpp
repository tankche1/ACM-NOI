# include<stdio.h>
# include<string.h>
# include<stack>
# include<algorithm>
using namespace std;
const int maxn=2010;

int up[maxn][maxn],left[maxn][maxn],right[maxn][maxn];
int n,m,a[maxn][maxn];
int ans_s=0,ans_area=0;

struct state{
	int pos,height;
};

void DP(){
	//for(int j=1;j<=m;j++) a[0][j]=-1;
	stack<state> q;
	state st;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			up[i][j]=a[i][j]==a[i-1][j]?up[i-1][j]+1:1;
		}
		a[i][m+1]=a[i][m]^1;
		a[i][0]=a[i][1];
		for(int j=1;j<=m+1;j++){
			st.pos=j,st.height=up[i][j];
			if(a[i][j]==a[i][j-1]){
			while((!q.empty())&&up[i][j]<=q.top().height) {
				st.pos=q.top().pos;
				ans_s=max(min(q.top().height,j-q.top().pos),ans_s);
				ans_area=max(ans_area,(q.top().height)*(j-q.top().pos));
				q.pop();
				}
			q.push(st);
			}
			else{
				while(!q.empty()){
				ans_s=max(min(q.top().height,j-q.top().pos),ans_s);
				ans_area=max(ans_area,(q.top().height)*(j-q.top().pos));
				q.pop();
				}
				q.push(st);
			}
		}
		q.pop();
	}
	return;
}

int main(){
	scanf("%d%d",&n,&m);
	memset(a,-1,sizeof(a));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);if((i+j)%2==0) a[i][j]^=1;
		}
	DP();

		printf("%d\n%d\n",ans_s*ans_s,ans_area);
	return 0;
}
