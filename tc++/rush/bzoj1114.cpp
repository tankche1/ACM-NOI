#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=2010;
const int maxm=4000010;
const int INF=~0U>>1;
char tmp[maxn][maxn],s[maxn][maxn];
int n;
int nB;
int mid1,mid2;
int delta1[maxn],delta2[maxn],len;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};

struct Boat{
	int x,y;
	Boat() {}
	Boat(int x,int y):x(x),y(y) {}
};
Boat B[maxm];
int BL[maxn],BR[maxn];
int half_len[maxn];
int up[maxn][maxn],down[maxn][maxn],stack[maxn],top;
int pre[maxn],next[maxn],can[maxn][maxn];
int vis[maxn][maxn];
Boat q[maxm];
int head=0,tail=-1;

void init(){
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	nB=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(s[i][j]=='r')
				B[nB++]=Boat(i,j);
		}
	bool ok=true;
	mid2=(B[0].x+B[nB-1].x)>>1;
	for(int i=0;i<nB;i++){
		if(s[B[i].x][B[i].y]!=s[mid2*2-B[i].x][B[i].y]) {ok=false;break;}
	}
	if(ok){
		//puts("fuck");
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			tmp[i][j]=s[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				s[i][j]=tmp[j][n-i+1];
		nB=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
			if(s[i][j]=='r')
				B[nB++]=Boat(i,j);
		}
	}
	half_len[0]=0;
	for(int i=0,j=0;i<nB;i++){
		for(j=i;j<nB-1&&B[j+1].x==B[i].x;j++);
		mid1=(B[i].y+B[j].y)>>1;
		half_len[B[i].x-B[0].x+1]=B[j].y-mid1+1;
		i=j;
	}
}

void prepare(){
	nB--;len=B[nB].x-B[0].x+1;
	//for(int i=1;i<=len;i++) printf("half[%d]:%d\n",i,half_len[i]);
	for(int i=1;i<=len;i++)
		delta1[i]=delta1[i-1]+(half_len[i-1]>half_len[i]);
	for(int i=len;i>=1;i--)
		delta2[i]=delta2[i+1]+(half_len[i]<half_len[i+1]);
	for(int i=1;i<=len;i++)
		if(delta1[i]==0&&delta2[i]==0) mid2=i;
		//	printf("mid2:%d\n",mid2);
	
	for(int i=1;i<=n;i++){
		pre[0]=n;
		for(int j=1;j<=n;j++)
			pre[j]=s[i][j]=='X'?0:pre[j-1]+1;
		next[n+1]=n;
		for(int j=n;j>=1;j--)
			next[j]=s[i][j]=='X'?0:next[j+1]+1;
		for(int j=1;j<=n;j++)
			can[i][j]=min(pre[j],next[j]);
	}
	
	for(int j=1;j<=n;j++){
		top=-1;
		for(int i=0;i<=mid2;i++) stack[++top]=i;
		for(int i=1;i<=n;i++){
			while(top&&can[i][j]<half_len[stack[top]]) top--;
			up[i][j]=stack[top];
			//printf("up[%d][%d]:%d\n",i,j,up[i][j]);
			if(stack[top]!=mid2)
				stack[++top]=up[i][j]+1;
		}
	}
	
	half_len[len+1]=0;
	for(int j=1;j<=n;j++){
		top=-1;
		for(int i=0;i<=len-mid2+1;i++) stack[++top]=i;
		for(int i=n;i>=1;i--){
			while(top&&can[i][j]<half_len[len+1-stack[top]]) top--;
			down[i][j]=stack[top];
			if(stack[top]!=len-mid2+1)
				stack[++top]=down[i][j]+1;
		}
	}
	/*for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(up[i][j]>=mid2&&down[i][j]>=len-mid2+1) printf("i:%d j:%d\n",i,j);*/
}

void BFS(){
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) vis[i][j]=INF;
	int ans=INF;
	q[++tail]=Boat(B[0].x+mid2-1,mid1);vis[B[0].x+mid2-1][mid1]=0;
	while(head<=tail){
		int x=q[head].x,y=q[head].y;head++;
	//	printf("vis[%d][%d]:%d\n",x,y,vis[x][y]);
		if(x==1||x==n||y==1||y==n){
			int res=INF;
			if(x==1) res=min(res,B[nB].x-mid2+1);
			if(x==n) res=min(res,mid2);
			if(y==1||y==n) res=min(res,half_len[mid2]);
			if(x==1&&(y==1||y==n)){
				for(int s=mid2;s<=len;s++)
					res=min(res,s-mid2+half_len[s]);
			}
			if(x==n&&(y==1||y==n)){
				for(int s=mid2;s>=0;s--)
					res=min(res,mid2-s+half_len[s]);
			}
			ans=min(ans,res+vis[x][y]);
		}
		for(int d=0;d<4;d++){
			int nx=x+dx[d],ny=y+dy[d];
			if(nx<1||nx>n||ny<1||ny>n||up[nx][ny]<mid2||down[nx][ny]<len-mid2+1||vis[nx][ny]!=INF) continue;
			q[++tail]=Boat(nx,ny);vis[nx][ny]=vis[x][y]+1;
		}
	}
	if(ans==INF) puts("NIE");
		else printf("%d\n",ans);
}

int main(){
	init();
	prepare();
	BFS();
	return 0;
}
/*
10
..........
..........
..r.......
.rrrX.....
rrrrr.....
.rrr......
X.r.......
.Xr.......
..........
..........
5
X.rX.
.rrrX
.rrrX
rrrrr
.....
6
..X.X.
X.rr.,
XrrrrX,
..rr.,
.....,
...X.,
8
.X..r...
X...r...
.rrrrrrr
.rrrrrrr
.rrrrrrr
....r..X
..XXrXXX
XXXXXXXX
*/
