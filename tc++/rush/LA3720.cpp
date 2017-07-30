# include<stdio.h>
# include<string.h>
# include<string>
# include<queue>
# include<map>
# include<math.h>
# include<algorithm>
using namespace std;
const double eps=1e-12;
struct State{
	double y,k;
	
	const bool operator < (const State &rhs)const{
		if(fabs(y-rhs.y)>eps)
		return y<rhs.y;
		if(fabs(k-rhs.k)>eps)
		return k<rhs.k;
		return false;
	}
};

int n,m;
map<State,int> sol;

int main(){
	while(scanf("%d%d",&n,&m)!=EOF){
		if(!n&&!m) break;
		sol.clear();
		State S;
		int ans=0;
		for(int x1=0;x1<n;x1++)
			for(int y1=0;y1<m;y1++){
				for(int x2=0;x2<n;x2++){
					if(x1==x2) continue;
						for(int y2=0;y2<m;y2++){
							if(y1==y2) continue;
							double kk=(double)(y2-y1)/(x2-x1);
							double yy=(double)y2-kk*x2;
							S.k=kk;S.y=yy;
							if(!sol.count(S)) {//printf("k:%.5lf y:%.5lf\n",S.k,S.y);
								sol[S]=1;
								ans++;}
						}
				}
			}
			printf("%d\n",ans);
	}
	return 0;
}
