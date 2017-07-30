# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
# define mp(a,b) make_pair(a,b)
using namespace std;
int a[50],b[50];
int sta,stb,eda,edb;
bool vis[50][50];
int front,rear;
pair<int,int> last[10000];
pair<int,int> q[10000];
inline int pos(int x,int y){return (x-1)*6+y;}

int dx[4]={1,0,0,-1},dy[4]={0,-1,1,0};
char op[4]={'D','L','R','U'};
int bit[4]={1,0,2,3};
vector<char> ans;

void bfs(){
	int ax,ay,bx,by;
	int nax,nay,nbx,nby;
	memset(vis,0,sizeof(vis));
	q[front=rear=1]=mp(sta,stb);vis[sta][stb]=1;
	while(front<=rear){
		if(q[front].first==eda&&q[front].second==edb) break;
		ax=(q[front].first+5)/6;ay=q[front].first-(ax-1)*6;
		bx=(q[front].second+5)/6;by=q[front].second-(bx-1)*6;
		//printf("front:%d ax:%d ay:%d bx:%d by:%d\n",front,ax,ay,bx,by);
		for(int i=0;i<4;i++){
			nax=ax+dx[i],nay=ay+dy[i];nbx=bx+dx[i],nby=by+dy[i];
			if((a[pos(ax,ay)]>>bit[i])&1) nax=ax,nay=ay;
			if((b[pos(bx,by)]>>bit[i])&1) nbx=bx,nby=by;
			if(vis[pos(nax,nay)][pos(nbx,nby)]==1) continue;
			//if(nax==ax&&nay==ay&&nbx==bx&&nby==by) continue;
			if(!(nax>=1&&nax<=6&&nay>=1&&nay<=6&&nbx>=1&&nbx<=6&&nby>=1&&nby<=6)) continue;
			if(((a[pos(nax,nay)]>>4)&1)==0) continue;
			if(((b[pos(nbx,nby)]>>4)&1)==0) continue;
			
			//printf("%d to %d by:%c\n",front,rear+1,op[i]);
			vis[pos(nax,nay)][pos(nbx,nby)]=1;
			q[++rear]=mp(pos(nax,nay),pos(nbx,nby));last[rear]=mp(front,i);
		}
		front++;
	}
	
	if(front>rear) {puts("-1");return;}
	ans.clear();
	rear=front;
	while(rear!=1){
		ax=(q[rear].first+5)/6;ay=q[rear].first-(ax-1)*6;
		//printf("ax:%d ay:%d\n",ax,ay);
		ans.push_back(op[last[rear].second]);
		rear=last[rear].first;
	}
	for(int i=(int)ans.size()-1;i>=0;i--) printf("%c",ans[i]);puts("");
}

int main(){
	int tcase;
	scanf("%d",&tcase);
	for(int i=1;i<=36;i++)
			scanf("%d",&a[i]);
	tcase--;
	while(tcase--){
		for(int i=1;i<=36;i++)
				scanf("%d",&b[i]);
		for(int i=1;i<=6;i++)
			for(int j=1;j<=6;j++){
				if((a[pos(i,j)]>>5)&1) sta=pos(i,j);
				if((a[pos(i,j)]>>6)&1) eda=pos(i,j);
				if((b[pos(i,j)]>>5)&1) stb=pos(i,j);
				if((b[pos(i,j)]>>6)&1) edb=pos(i,j);
			}
		
		bfs();
		for(int i=1;i<=36;i++)
			a[i]=b[i];
	}
	return 0;
}
