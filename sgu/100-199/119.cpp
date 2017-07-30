# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;

inline int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
int n,a1,b1;
vector<pair<int,int> > ans;
int main(){
	scanf("%d%d%d",&n,&a1,&b1);
	int c=n/gcd(n,a1),d=n/gcd(n,b1);
	int e=c*d/gcd(c,d);
	//printf("%d %d %d\n",c,d,e);
	int nowc=0,nowd=0;
	for(int i=1;i<=e;i++){
		nowc=(nowc+a1)%n;nowd=(nowd+b1)%n;
		ans.push_back(make_pair(nowc,nowd));
	}
	sort(ans.begin(),ans.end());
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++){
		printf("%d %d\n",ans[i].first,ans[i].second);
	}
	return 0;
}
