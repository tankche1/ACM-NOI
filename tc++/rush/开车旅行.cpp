# include<stdio.h>
# include<string.h>
# include<math.h>
# include<set>
# include<map>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxk=16;
int maxj;
typedef long long LL;
int q[maxn][2];
int n,m;LL x0;
LL h[maxn];
map<int,int> id;
set<int> s;
typedef set<int> ::iterator it;
inline LL dist(int a,int b){
	if(b==n+1) return 0;
	//if(a==13&&b==19) printf(" a:%d b:%d %lld %lld %lld\n",a,b,(h[a]-h[b])<0?h[b]-h[a]:h[a]-h[b],h[a],h[b]);
	return (h[a]-h[b])<0?h[b]-h[a]:h[a]-h[b];
}
struct state{
	int to;
	LL A,B;//A走的路程 B走的路程
	state() {A=0;B=0;}
	state(int to,LL A,LL B):to(to),A(A),B(B) {}
};
state dp[maxn][maxk][1];//[0] 小A先走

void make_way(){
	q[n+1][0]=q[n+1][1]=n+1;
	for(int i=n;i>=1;i--){
		it small=s.lower_bound(h[i]),big=s.lower_bound(h[i]),use;
		if(i==n) q[i][0]=q[i][1]=n+1;
			else if(i==n-1) q[i][0]=n+1,q[i][1]=n;
				else{
					for(int j=1;j>=0;j--){
						if(small==s.begin()) {use=big++;}
						else if(big==s.end()) {use=--small;}
						else {small--;use=(h[i]-*(small))<=(*big-h[i])?small:big;if(use==big) small++,big++;}
						q[i][j]=id[*use];
					}
				}
				if(!id.count(h[i])){
					//printf("id:%d\n",h[i]);
				s.insert(h[i]);
				id[h[i]]=i;
				}
				//printf("q[%d][0]:%d q[%d][1]:%d\n",i,q[i][0],i,q[i][1]);
	}
}

void cal_dp(){
	for(int i=1;i<=n+1;i++){
		dp[i][0][0].A=dist(i,q[i][0]);//dp[i][0][1].B=dist(i,q[i][1]);
		dp[i][0][0].to=q[i][0];//dp[i][0][1].to=q[i][1];
	}
	for(int i=1;i<=n+1;i++){
		dp[i][1][0]=state(q[q[i][0]][1],dist(i,q[i][0]),dist(q[i][0],q[q[i][0]][1]));
		dp[i][1][1]=state(q[q[i][1]][0],dist(i,q[i][1]),dist(q[i][1],q[q[i][1]][0]));
		//if(i==13) printf("dp[%d][%d] to:%d A:%lld B:%lld\n",i,1,dp[i][1][0].to,dp[i][1][0].A,dp[i][1][0].B);
	}
	for(int j=2;;j++){
		bool ok=false;
		for(int i=1;i<=n+1;i++){
			for(int w=0;w<1;w++){
				dp[i][j][w]=state(dp[dp[i][j-1][w].to][j-1][w].to,dp[i][j-1][w].A+dp[dp[i][j-1][w].to][j-1][w].A,dp[i][j-1][w].B+dp[dp[i][j-1][w].to][j-1][w].B);
				if(dp[i][j][w].to!=n+1) ok=true;
				//if(i==13)	printf("dp[%d][%d] to:%d A:%lld B:%lld\n",i,j,dp[i][j][0].to,dp[i][j][0].A,dp[i][j][0].B);
			}
		}
		if(!ok) {maxj=j;break;}
	}
}

void solve_x0(){
		scanf("%lld",&x0);
	LL ansA,ansB;
	int ans;
	bool first=true;
	for(int i=1;i<=n;i++){
		int now=i;LL xx=x0;LL A=0,B=0;
		for(int j=maxj;j>=0;j--){
			if(now==n+1) break;
			if((LL)(dp[now][j][0].A+dp[now][j][0].B)<=(LL)xx){
				xx-=dp[now][j][0].A+dp[now][j][0].B;
				A+=dp[now][j][0].A;B+=dp[now][j][0].B;
				now=dp[now][j][0].to;
			}
		}
		if(B==0) continue;
		if(first||ansA*B>A*ansB||(ansA*B==A*ansB&&h[i]>h[ans])){
			first=false;ansA=A;ansB=B;ans=i;
		}
	}
	if(!first)
	printf("%d\n",ans);
}

void solve(int start,LL x){
	int now=start;LL xx=x;
	LL A=0,B=0;
	for(int j=maxj;j>=0;j--){
			if(now==n+1) break;
			if((LL)(dp[now][j][0].A+dp[now][j][0].B)<=(LL)xx){
				xx-=dp[now][j][0].A+dp[now][j][0].B;
				A+=dp[now][j][0].A;B+=dp[now][j][0].B;
			//	if(start==13) printf("%d to %d A:%lld B:%lld\n",now,dp[now][j][0].to,A,B);
				now=dp[now][j][0].to;
			}
		}
		printf("%lld %lld\n",A,B);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&h[i]);
	make_way();
	cal_dp();
	solve_x0();
	int start;LL x;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%lld",&start,&x);
		solve(start,x);
	}
	return 0;
}
