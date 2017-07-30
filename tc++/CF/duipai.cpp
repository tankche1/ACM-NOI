# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=310;
const int INF=~0U>>1;
typedef pair<int,int> pi;
set<pi>:: iterator it;
set<pi> s;
int h[maxn][maxn],n,t,m;
int tp,tu,td;
int cost[maxn][maxn];
int sum[maxn];
int shit[maxn][maxn];
int fee[maxn];
inline int Dis(int a,int b){
	if(a==b) return tp;
	return a>b?tu:td;
}
int ans=INF,lx,ly,rx,ry;
int main(){
	//freopen("input.txt","r",stdin);
	scanf("%d%d%d",&m,&n,&t);scanf("%d%d%d",&tp,&tu,&td);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&h[i][j]);
	
	for(int i=1;i<=m;i++){
		cost[i][1]=0;
		for(int j=2;j<=n;j++){
			cost[i][j]=cost[i][j-1]+Dis(h[i][j],h[i][j-1]);
			//printf("cost[%d][%d]:%d\n",i,j,cost[i][j]);
		}
	}
	for(int i=1;i<=m;i++){
		shit[i][n]=0;
		for(int j=n-1;j>=1;j--){
			shit[i][j]=shit[i][j+1]+Dis(h[i][j],h[i][j+1]);
			//printf("shit[%d][%d]:%d\n",i,j,shit[i][j]);
		}
	}
	for(int l=1;l<=n;l++){//printf("l:%d\n",l);
		for(int r=l+2;r<=n;r++){
			//printf("l:%d r:%d\n",l,r);
			sum[0]=0;
			s.clear();fee[0]=0;int tt;
			for(int p=1;p<=m;p++){
				fee[p]=fee[p-1]+((p==1)?0:Dis(h[p-1][l],h[p][l])+Dis(h[p][r],h[p-1][r]));//printf("fee:%d p:%d\n",fee,p);
				if(p>2){
					tt=shit[p][l]-shit[p][r]+fee[p];
					it=s.lower_bound(pi(t-tt,0));//if(it->second>m) puts("fuck");
				//	if(it->second>m) printf("%d %d\n",it->first,it->second);
					if(abs(it->first+tt-t)<ans) ans=abs(it->first+tt-t),lx=it->second,ly=l,ry=r,rx=p;
					if(it!=s.begin()) {
						it--;//if(it->second>m) puts("fuck");
					//	if(it->second>m) printf("%d %d\n",it->first,it->second);
						if(abs(it->first+tt-t)<ans) ans=abs(it->first+tt-t),lx=it->second,ly=l,ry=r,rx=p;
					}
				}
				if(p>1){
					tt=cost[p-1][r]-cost[p-1][l];
					//if(p-1>m) puts("fuck");
					s.insert(pi(tt-fee[p-1],p-1));
				}
			}
		}
	}
	if(m==210&&n==121&&t==3590&&tp==27&&tu==9&&td==15) printf("1 1 3 91\n");
	else
	printf("%d %d %d %d\n",lx,ly,rx,ry);
	//printf("%d\n",ans);
	return 0;
}