# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
typedef pair<int,int> pi;

pi start,end;
pi D[]={pi(1,2),pi(2,1),pi(-1,-2),pi(-2,-1),pi(1,-2),pi(2,-1),pi(-1,2),pi(-2,1)};

pi dist(pi a,pi b){
	int x=abs(b.first-a.first),y=abs(b.second-a.second);
	return pi(x+y,abs(x-y));
}

pi operator + (pi a,pi b){
	return pi(a.first+b.first,a.second+b.second);
}

bool vis[110][110];

int ans=0;
int main(){
	scanf("%d%d%d%d",&start.first,&start.second,&end.first,&end.second);
	while(dist(start,end).first>10){
		pi a,Min(INF,INF),next;
		for(int i=0;i<8;i++){
			a=start+D[i];if(dist(a,end)<Min){
				Min=dist(a,end);
				next=a;
			}
		}
		start=next;ans++;
	}
	//printf("ans:%d start:%d %d\n",ans,start.first,start.second);
	pi st(0,0),ed(abs(end.first-start.first),abs(end.second-start.second));
	memset(vis,false,sizeof(vis));
	if(st==ed) {puts("0");return 0;}
	queue<pi> q;queue<int> d;q.push(st);vis[0+50][0+50]=1;d.push(0);
	while(!q.empty()){
		pi now=q.front();q.pop();int dis=d.front();d.pop();
		for(int i=0;i<8;i++){
			pi next=now+D[i];
			if(!vis[next.first+50][next.second+50]){
				vis[next.first+50][next.second+50]=1;q.push(next);d.push(dis+1);
				if(next==ed) {printf("%d\n",dis+1+ans);return 0;}
			}
		}
	}
	return 0;
}
