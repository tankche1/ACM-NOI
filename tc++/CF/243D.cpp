# include<stdio.h>
# include<string.h>
# include<vector>
# include<map>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100001;
vector<int> p[maxn];
typedef pair<int,int> pi;

map<pi,int> id;

/*bool find(int x,int y){
	if(x>=maxn) return false;
	int t=lower_bound(p[x].begin(),p[x].end(),y)-p[x].begin();
	printf("%d %d have:%d\n",x,y,p[x][t]==y);
	return p[x][t]==y;
}*/
bool find(int x,int y){
	return id.count(pi(x,y));
}

int main(){
	int x,y,n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);p[x].push_back(y);id[pi(x,y)]=1;
	}
	for(int i=0;i<maxn;i++) sort(p[i].begin(),p[i].end());
	int half=(int)sqrt(n);
	int ans=0;
	for(int x=0;x<maxn;x++){
		int num=p[x].size();
		if(!num) continue;
		if(num<half){
			for(int i=0;i<num;i++)
				for(int j=i+1;j<num;j++){
					int d=p[x][j]-p[x][i];
					if(find(x+d,p[x][i])&&find(x+d,p[x][j]))
						ans++;
				}
		}
		else{
			for(int nx=x+1;nx<maxn;nx++){
				int d=nx-x;
				for(int j=0;j<p[nx].size();j++)
					if(find(nx,p[nx][j]+d)&&find(x,p[nx][j])&&find(x,p[nx][j]+d))
						ans++;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
