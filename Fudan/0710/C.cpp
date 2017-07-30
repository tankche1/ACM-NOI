# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
# define r(a,b) A[a].push_back(b);
using namespace std;
vector<int> A[40],belong[40];
bool used[40][40];

void init(){
	memset(A,0,sizeof(A));
	r(1,1) r(1,2)
	r(2,3) r(2,4) r(2,5) r(2,6) r(2,7)
	r(3,8) r(3,9) r(3,10) r(3,11) r(3,12) r(3,13)
	r(4,14) r(4,15) r(4,16) r(4,17) r(4,18)
	r(5,19) r(5,20) r(5,21) r(5,22) r(5,23) r(5,24)
	r(6,25) r(6,26) r(6,27) r(6,28) r(6,29)
	r(7,30) r(7,31)
	
	r(8,3) r(8,8)
	r(9,1) r(9,4) r(9,9) r(9,14) r(9,19)
	r(10,2) r(10,5) r(10,10) r(10,15) r(10,20) r(10,25)
	r(11,6) r(11,11) r(11,16) r(11,21) r(11,26)
	r(12,7) r(12,12) r(12,17) r(12,22) r(12,27) r(12,30)
	r(13,13) r(13,18) r(13,23) r(13,28) r(13,31)
	r(14,24) r(14,29)
	
	r(15,7) r(15,13)
	r(16,2) r(16,6) r(16,12) r(16,18) r(16,24)
	r(17,1) r(17,5) r(17,11) r(17,17) r(17,23) r(17,29)
	r(18,4) r(18,10) r(18,16) r(18,22) r(18,28)
	r(19,3) r(19,9) r(19,15) r(19,21) r(19,27) r(19,31)
	r(20,8) r(20,14) r(20,20) r(20,26) r(20,30)
	r(21,19) r(21,25)
	
	r(22,1) r(22,2) r(22,4) r(22,5) r(22,6) r(22,10) r(22,11)
	r(23,3) r(23,4) r(23,8) r(23,9) r(23,10) r(23,14) r(23,15)
	r(24,6) r(24,7) r(24,11) r(24,12) r(24,13) r(24,17) r(24,18)
	r(25,10) r(25,11) r(25,15) r(25,16) r(25,17) r(25,21) r(25,22)
	r(26,14) r(26,15) r(26,19) r(26,20) r(26,21) r(26,25) r(26,26)
	r(27,17) r(27,18) r(27,22) r(27,23) r(27,24) r(27,28) r(27,29)
	r(28,21) r(28,22) r(28,26) r(28,27) r(28,28) r(28,30) r(28,31)
	
	//r(29,5) r(29,9) r(29,12) r(29,16) r(29,20) r(29,23) r(29,27)
	
	for(int i=1;i<=29;i++)
		for(int j=0;j<(int)A[i].size();j++)
			belong[A[i][j]].push_back(i);
}

int k,n,ans=0;
int p[40];
bool vis[40][40];

bool dfs(int cur){
	if(cur==32) {ans++;if(ans==n) return true;else return false;}
	if(p[cur]!=0) {return dfs(cur+1);}
	memset(vis[cur],false,sizeof(vis[cur]));
	for(int i=0;i<(int)belong[cur].size();i++){
		for(int j=0;j<(int)A[belong[cur][i]].size();j++)
			vis[cur][p[A[belong[cur][i]][j]]]=1;
	}
	for(int i=1;i<=k;i++){
		if(vis[cur][i]) continue;
		p[cur]=i;
		if(dfs(cur+1)) return true;
		p[cur]=0;
	}
	return false;
}

int main(){
	init();
	scanf("%d%d",&k,&n);
	for(int i=1;i<=31;i++)
		scanf("%d",&p[i]);
	memset(used,false,sizeof(used));
	bool wrong=false;
	for(int i=1;i<=31;i++)
		if(p[i]!=0){
			for(int j=0;j<(int)belong[i].size();j++){
				if(used[belong[i][j]][p[i]]) wrong=true;
				used[belong[i][j]][p[i]]=1;
			}
		}
	if(wrong) {puts("No way");return 0;}
	dfs(1);
	if(ans!=n) {puts("No way");return 0;}
	puts("Found");
	for(int i=1;i<=31;i++) printf("%d ",p[i]);puts("");
	return 0;
}
