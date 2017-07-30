# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
const double eps=1e-8;

struct Point{
	double x,y;
};
Point p[110];
struct que{
	double x,a1,b1,a2,b2;
};
que Q[25];
int cnt=0;
int n;
double f[100][100];
double d[100];
bool inq[110];
	
void spfa(){
	for(int i=1;i<cnt;i++) d[i]=INF;
		d[0]=0;memset(inq,false,sizeof(inq));
	queue<int> q;q.push(0);
	while(!q.empty()){
		int x=q.front();q.pop();inq[x]=false;
		for(int i=0;i<cnt;i++)
			if(f[x][i]!=-INF){
				if(d[i]>d[x]+f[x][i]){
					d[i]=d[x]+f[x][i];
					if(!inq[i]){
						inq[i]=true;q.push(i);
					}
				}
			}
	}
}

int main(){
	cnt=0;
	scanf("%d",&n);
	p[cnt].x=0;p[cnt++].y=5;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf%lf%lf",&Q[i].x,&Q[i].a1,&Q[i].b1,&Q[i].a2,&Q[i].b2);
		p[cnt].x=Q[i].x;p[cnt++].y=Q[i].a1;
		p[cnt].x=Q[i].x;p[cnt++].y=Q[i].b1;
		p[cnt].x=Q[i].x;p[cnt++].y=Q[i].a2;
		p[cnt].x=Q[i].x;p[cnt++].y=Q[i].b2;
	}
	p[cnt].x=10;p[cnt++].y=5;
	for(int i=0;i<cnt;i++) for(int j=0;j<cnt;j++) f[i][j]=-INF;
	for(int i=0;i<cnt;i++){
		for(int j=i+1;j<cnt;j++){
			if(p[j].x>p[i].x){
				bool ok=true;
				for(int k=1;k<=n;k++){
					if(Q[k].x>p[i].x&&Q[k].x<p[j].x){
						double dot=(double)(p[j].y-p[i].y)/(p[j].x-p[i].x)*(Q[k].x-p[i].x)+p[i].y;
						if((fabs(dot-Q[k].a1)>eps&&dot<Q[k].a1)||(fabs(dot-Q[k].b2)>eps&&dot>Q[k].b2)||(fabs(dot-Q[k].b1)>eps&&fabs(dot-Q[k].a2)>eps&&dot>Q[k].b1&&dot<Q[k].a2))
						{ok=false;break;}
					}
				}
				if(ok){ f[i][j]=sqrt((p[j].y-p[i].y)*(p[j].y-p[i].y)+(p[j].x-p[i].x)*(p[j].x-p[i].x));
				//	printf("f[%d][%d]:%.3lf %.3lf %.3lf \n",i,j,f[i][j],(p[j].y-p[i].y),(p[j].x-p[i].x));
				}
			}
		}
	}
	spfa();
	printf("%.2lf\n",d[cnt-1]);
	return 0;
}
